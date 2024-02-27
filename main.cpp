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




class IAccesble
{
    virtual void accept(NodeAccessor) = 0;
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

    void accept(NodeAccessor a)
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
    void operator()(TestNode& tn)
    {
        tn.test();
        std::cout << "no jestem ciekaw" << std::endl;

    }

    void operator()(std::weak_ptr<TestNode> sp)
    {
        std::cout << "a to z sp" << std::endl;
    }
};





using TestNodeVisitor = ConcreteVisitor<TestNode>;

TestNodeVisitor cv;

int main()
{
    {


        Node<Resources> n(std::make_shared<TestNode>(0));
        NodeAccessor a = cv;
        n.accept(a);

        // NodePack v;
        // {
        //     //v.push_back(TestNode(3));
        //     v.push_back(std::make_shared<TestNode>(0));

        //     NodeAccessor a = cv;
        //     v[0].accept(cv);
        //     //v[1].accept(cv);
        // }
        
        // Resources res;
        // v.update(0.0, res);

    }

    std::cin.get();
    return 0;
}