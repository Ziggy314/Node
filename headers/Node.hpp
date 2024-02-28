
#pragma once

#include <memory>
#include <iostream>
#include <any>

template<typename T>
struct ConcreteVisitor
{
    template<typename VisitedT>
    void operator()(VisitedT& )
    {
        std::cout << "tu nie" <<std::endl;
    }
};

struct NodeAccessor
{
    template<typename T>
    void Acess(T& t)
    {
        (*reinterpret_cast<ConcreteVisitor<T>*>(_any))(t);
    }

    template<typename VisitorT>
    NodeAccessor(VisitorT& accesor):
       _any(&accesor)
    {}

    void* _any;
    
    // tu jest problem bo trzeba dodawać funkcje dla każdego nowego typu
};


namespace nodeImpl_
{
    //ToPtr struct and specialization for sharedPtr is needed to call function on it always in the same way.
    //std::shared<X> sx = ...
    //X x;
    //ToPtr<X>(sx)->AnyoperationOn_X() (dot operator is replaced with ->)
    //ToPtr<std::shared<X>>(sx)->AnyoperationOn_X() (generaly do nothing)
    template<typename T>
    struct ToPtr {   
        T& t_;
        ToPtr(T& t):t_(t){}

        inline T* operator->() {
            return &t_;
        }

        inline T& operator*(){
            return t_;
        }
    };

    template <typename T>
    struct ToPtr<std::shared_ptr<T>> {
        std::shared_ptr<T>& t_;
        ToPtr(std::shared_ptr<T> t) noexcept:t_(t){}

        inline std::shared_ptr<T> operator->() {
            return t_;
        }
        inline std::shared_ptr<T> operator*(){
            return t_;
        }
    };


    template<typename T>
    auto ConvertToPtr(T& t) 
    {
        return ToPtr<T>(t).operator->();
    }

    //to do fix it
    // template<typename T>
    // auto ConvertToRef(T& t) 
    // {
    //     return ToPtr<T>(t).operator*();
    // }

}//~ namespace nodeImpl_


template<typename ResourceT>
class Node
{
public:

template<typename ObjType>
Node(ObjType s): 
    ptrToNode_(std::make_unique<NodeOwner<ObjType>>(std::move(s))) {}

Node(const Node& s): 
    ptrToNode_(s.ptrToNode_->copy_()){}

Node(Node&& s) noexcept = default; 

Node& operator=(const Node& x) {
    return *this = Node(x);
}

Node& operator=(Node&& x) noexcept = default;

void update(double t, ResourceT res) {
   ptrToNode_->update(t, res);
} 

void accept(NodeAccessor& a) {
    ptrToNode_->accept(a);
}

private:
struct NodeBase {
    virtual void update(double, ResourceT) = 0;
    virtual void accept(NodeAccessor&) = 0;
    virtual std::unique_ptr<NodeBase> copy_() = 0;
    virtual ~NodeBase() = default;
};

template<typename ObjType>
struct NodeOwner final: 
    public NodeBase {
    
    NodeOwner(ObjType r) :
        node_(std::move(r)) {
    }

    NodeOwner(NodeOwner<ObjType>& r) :
        node_(std::forward<ObjType>(r.node_)) {
    }

    std::unique_ptr<NodeBase> copy_() override {
        return std::make_unique<NodeOwner<ObjType>>(*this);
    }
    
    ~NodeOwner() = default;

    void update(double t, ResourceT res) override {
        nodeImpl_::ConvertToPtr(node_)->update(t, res);
    }

    void accept(NodeAccessor& a) override {
        a.Acess(node_);
    }
private:
    ObjType node_;
};
std::unique_ptr<NodeBase> ptrToNode_;
};
