#pragma once

#include "../NodeImpl/Node.hpp"
#include "../NodeImpl/Resources.hpp"
#include "../NodeImpl/VisitorBase.hpp"

#include <iostream>


class Root
{
public:
    void update(double t, Resources)
    {
        std::cout << "Root::Update" << std::endl;
    }

    void accept(NodeAccessor& accessor)
    {
        accessor.Acess(*this);
    }

    void HelloFromRoot()
    {
        std::cout << "HelloFromRoot" << std::endl;
    }
};

template<>
struct ConcreteVisitor<Root> {
    template<typename T>
    ConcreteVisitor<Root>(T t): _f(t) {
    }

    void operator()(Root& root) {      
        _f(root);
    }
private:
    std::function<void(Root&)> _f;
};

template<>
struct ConcreteVisitor<std::shared_ptr<Root>>
{
    template<typename T>
    ConcreteVisitor(T f): _f(f) {
    }

    void operator()(std::weak_ptr<Root> sp) {      
        _f(sp);
    }
private:
    std::function<void(std::weak_ptr<Root>)> _f;
};

using shared_ptr_RootVisitor = ConcreteVisitor<std::shared_ptr<Root>>;
using RootVisitor = ConcreteVisitor<Root>;



//using RootVisitor_sp = ConcreteVisitor<std::shared_ptr<Root>>;

