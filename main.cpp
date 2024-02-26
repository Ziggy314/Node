#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <functional>
#include "headers/Node.hpp"

class IAccesble;
class TestNode;


class Resources
{
};

class IAccesble
{
    virtual void accept(DataAccessor&) = 0;
};


struct TestNode : public IAccesble
{
    
    TestNode(int i):
        _i(std::make_unique<int>(i))
    {
        std::cout << "TestNode::Ctor" <<std::endl;
    }

    TestNode(const TestNode&) = delete;

    TestNode(TestNode&& i) noexcept:
        _i(std::move(i._i))
    {
        std::cout << "TestNode::move" <<std::endl;
    }

    TestNode& operator=(const TestNode& u) = delete;

    TestNode& operator=(TestNode&& u) = delete;

    ~TestNode()
    {
        std::cout << "TestNode::dtor" <<std::endl;
    }

    void accept(DataAccessor& a)
    {
        a.Acess(*this);
    }

    void update(double t, Resources r )
    {
        std::cout << "u = " << t <<std::endl;
    }


    std::unique_ptr<int> _i;
};



class NodePack: std::vector<Node<Resources>>
{
    typedef std::vector<Node<Resources>> Base;
    public:

    using Base::push_back;
    using Base::operator[];

    void update(double t, Resources res) {
        for (auto& x: *this)
            x.update(t, res);
    }
};


int main()
{
    {
        DataAccessor a;
        NodePack v;
        {

            v.push_back(TestNode(3));
            v.push_back(std::make_shared<TestNode>(0));

            v[0].accept(a);
        }
        
        Resources res;
        v.update(0.0, res);

    }

    std::cin.get();
    return 0;
}