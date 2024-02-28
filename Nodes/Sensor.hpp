#pragma once

#include "../NodeImpl/Node.hpp"
#include "../NodeImpl/Resources.hpp"
#include "../NodeImpl/VisitorBase.hpp"

#include <iostream>


class Sensor
{
public:
    void update(double t, Resources)
    {
        std::cout << "Sensor::Update" << std::endl;
    }

    void accept(NodeAccessor& accessor)
    {
        accessor.Acess(*this);
    }

    void HelloFromSensor()
    {
        std::cout << "HelloFromSensor" << std::endl;
    }
};

template<>
struct ConcreteVisitor<Sensor> {
    template<typename T>
    ConcreteVisitor<Sensor>(T t): _f(t) {
    }

    void operator()(Sensor& root) {      
        _f(root);
    }
private:
    std::function<void(Sensor&)> _f;
};

template<>
struct ConcreteVisitor<std::shared_ptr<Sensor>>
{
    template<typename T>
    ConcreteVisitor(T f): _f(f) {
    }

    void operator()(std::weak_ptr<Sensor> sp) {      
        _f(sp);
    }
private:
    std::function<void(std::weak_ptr<Sensor>)> _f;
};

using shared_ptr_SensorVisitor = ConcreteVisitor<std::shared_ptr<Sensor>>;
using SensorVisitor = ConcreteVisitor<Sensor>;
