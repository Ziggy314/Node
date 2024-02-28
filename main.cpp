#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <functional>
#include "NodeImpl/Node.hpp"
#include "NodeImpl/NodePack.hpp"
#include "NodeImpl/Resources.hpp"
#include <thread>


#include <benchmark/benchmark.h>

#include "Nodes/Root.hpp"
#include "Nodes/Sensor.hpp"



// class IAccesble
// {
//     virtual void accept(NodeAccessor&) = 0;
//     virtual void update(double t, Resources r );
// };


shared_ptr_RootVisitor rootVisitor = [](std::weak_ptr<Root> r){r.lock()->HelloFromRoot();};
SensorVisitor sensorVisitor = [](Sensor& s){s.HelloFromSensor();};


int main()
{
    NodeAccessor accessor1 = rootVisitor;
    Node<Resources> node(std::make_shared<Root>());
    node.accept(accessor1);

    NodePack colection;
    colection.push_back(std::move(node));
    colection.push_back(Sensor());

    for(int i = 0; i < 100; ++i)
    {   
        colection.update(i, Resources());
        NodeAccessor temp = sensorVisitor;
        colection[1].accept(temp);
    }

    std::cin.get();
    return 0;
}