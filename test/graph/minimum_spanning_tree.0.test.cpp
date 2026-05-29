// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/minimum_spanning_tree

#include "node_pool.hpp"
#include "st_tree_node_base.hpp"
#include <iostream>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    struct Node : STTreeNodeBase<Node> {
        bool IsEdge = false;
        int From, To, W;
        Node *Max = nullptr;
        std::multiset<Node *, bool (*)(Node *, Node *)>::iterator iter;

        void do_update() {
            Max = IsEdge ? this : nullptr;
            if (left()) {
                if (Max == nullptr || (left()->Max != nullptr && left()->Max->W > Max->W))
                    Max = left()->Max;
            }
            if (right()) {
                if (Max == nullptr || (right()->Max != nullptr && right()->Max->W > Max->W))
                    Max = right()->Max;
            }
        }
    };
    FixedSizeNodePool<Node> pool(n + m);
    std::multiset<Node *, bool (*)(Node *, Node *)> used(
        [](Node *a, Node *b) { return a->W < b->W; });
    auto [node, id] = pool.get_func();
    for (int i = 0; i < m; ++i) {
        Node *e   = node(n + i);
        e->IsEdge = true;
        std::cin >> e->From >> e->To >> e->W;
        e->update();
        if (e->From == e->To) continue;
        Node *u = node(e->From);
        Node *v = node(e->To);
        if (u->root() != v->root()) {
            u->link(e);
            v->link(e);
            e->iter = used.insert(e);
        } else {
            u->evert();
            v->expose();
            Node *max = v->Max;
            if (max->W > e->W) {
                max->cut(node(max->From));
                max->cut(node(max->To));
                used.erase(max->iter);
                u->link(e);
                v->link(e);
                e->iter = used.insert(e);
            }
        }
    }
    long long sum = 0;
    for (auto &&e : used) sum += e->W;
    std::cout << sum << '\n';
    for (auto &&e : used) std::cout << id(e) - n << ' ';
    return 0;
}
