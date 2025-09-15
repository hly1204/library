#pragma once

#include <list>
#include <memory>
#include <utility>
#include <vector>

template<typename NodeT> class FixedSizeNodePool {
    std::vector<NodeT> pool;

public:
    explicit FixedSizeNodePool(int n) : pool(n) {}
    NodeT *at(int ind) { return pool[ind]; }
    int id(NodeT *a) const { return a - pool.data(); }
    auto get_func() {
        return std::make_pair([this](int ind) { return at(ind); },
                              [this](NodeT *a) { return id(a); });
    }
};

template<typename NodeT> class DynamicSizeNodePool {
    struct Wrapped : public NodeT {
        using NodeT::NodeT;
        typename std::list<Wrapped>::iterator i;
    };
    std::list<Wrapped> used_list;
    std::list<Wrapped> free_list;

public:
    template<typename... Args> NodeT *make(Args &&...arg) {
        if (free_list.empty()) {
            auto &&node = used_list.emplace_back(std::forward<Args>(arg)...);
            node.i      = std::prev(used_list.end());
            return std::addressof(node);
        }
        used_list.splice(used_list.end(), free_list, std::prev(free_list.end()));
        auto &&node = used_list.back();
        node.~NodeT(); // i remains unchanged
        new (std::addressof(node)) NodeT(std::forward<Args>(arg)...);
        return std::addressof(node);
    }
    // this is lazy, if sth. relies on the order of dtor, do NOT use
    void retrieve(NodeT *node) {
        free_list.splice(free_list.end(), used_list, ((Wrapped *)node)->i);
    }
};
