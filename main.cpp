#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <functional>
#include "headers/Node.hpp"
#include "headers/NodePack.hpp"
#include "headers/Resources.hpp"
#include <any>


#include <benchmark/benchmark.h>



class IAccesble
{
    virtual void accept(NodeAccessor&) = 0;
};

struct TestNode : public IAccesble
{
    TestNode(int i)//:_i(std::make_unique<int>(i))
    {}
    
    TestNode(const TestNode&) = default;

    TestNode(TestNode&& i) noexcept//:_i(std::move(i._i))
    { }

    TestNode& operator=(const TestNode& u) = delete;

    TestNode& operator=(TestNode&& u) = delete;

    ~TestNode() = default;

    void accept(NodeAccessor& a)
    {
        a.Acess(*this);
    }

    void update(double t, Resources r )
    {
        std::cout << "u = " << t <<std::endl;
    }

    void test()
    {
        std::cout << "TestNode::test" <<std::endl;
    }

    //std::unique_ptr<int> _i; // to jest tylko testowa zmienna żeby sprawdzić czy dane się dobrze przenoszą 
};


template<>
struct ConcreteVisitor<std::shared_ptr<TestNode>>
{
    void operator()(std::weak_ptr<TestNode> sp)
    {
        //std::cout << "a to z sp" << std::endl;
    }
};
using TestNodeSpVisitor = ConcreteVisitor<std::shared_ptr<TestNode>>;

template<>
struct ConcreteVisitor<TestNode>
{
    void operator()(TestNode& tn)
    {
        //std::cout << "TestNode visitor" << std::endl;
    }
};
using TestNodeVisitor = ConcreteVisitor<TestNode>;


TestNodeVisitor nodeVisitor;
TestNodeSpVisitor spNodeVisitor;


static void BM_executeByval(benchmark::State& state) {
    NodeAccessor accessor = nodeVisitor;
    Node<Resources> node(TestNode(2));
    for (auto _ : state)
    {
        node.accept(accessor);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_executeByval);


static void BM_executeSp(benchmark::State& state) {
    NodeAccessor accessor = spNodeVisitor;
    auto tn = std::make_shared<TestNode>(2);
    Node<Resources> node1(tn);
    for (auto _ : state)
    {
        node1.accept(accessor);
    }
}
BENCHMARK(BM_executeSp);


BENCHMARK_MAIN();


// int main()
// {
//     NodeAccessor accessor1 = spNodeVisitor;
//     NodeAccessor accessor2 = nodeVisitor;
//     auto tn = std::make_shared< TestNode>(2);
//     Node<Resources> node1(tn);
//     Node<Resources> node2(TestNode(2));
//     node1.accept(accessor1);
//     node2.accept(accessor2);
    


//     // {
//     //     NodePack v;
//     //     {
//     //         v.push_back(TestNode(3));
//     //         v.push_back(std::make_shared<TestNode>(0));

//     //         NodeAccessor na = nodeVisitor;
//     //         v[0].accept(na);
//     //         v[1].accept(na);
//     //     }
        
//     //     Resources res;
//     //     v.update(0.0, res);

//     // }

//     std::cin.get();
//     return 0;
// }