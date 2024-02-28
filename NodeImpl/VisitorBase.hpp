#pragma once
#include <functional>

template<typename FunctionType>
struct VisitorBase
{

    template<typename AnyF>
    VisitorBase(AnyF f): _f(f){}

    std::function<void(FunctionType)> _f;
};
