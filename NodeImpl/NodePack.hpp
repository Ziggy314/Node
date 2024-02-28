#pragma once 

#include "Node.hpp"
#include "Resources.hpp"
#include <vector>



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