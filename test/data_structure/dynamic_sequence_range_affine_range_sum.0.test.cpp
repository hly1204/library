#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include "modint.hpp"
#include "treap_node_base.hpp"
#include <iostream>
#include <memory>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    struct TreapNode : TreapNodeBase<TreapNode> {
        mint Val, Sum, Add, Mul = {1};
        void do_propagate() {
            if (left()) {
                left()->Add = Mul * left()->Add + Add;
                left()->Mul *= Mul;
                left()->Sum = Add * left()->size() + Mul * left()->Sum;
            }
            if (right()) {
                right()->Add = Mul * right()->Add + Add;
                right()->Mul *= Mul;
                right()->Sum = Add * right()->size() + Mul * right()->Sum;
            }
            Val = Add + Mul * Val;
            Add = 0;
            Mul = 1;
        }
        void do_update() {
            Sum = Val;
            if (left()) Sum += left()->Sum;
            if (right()) Sum += right()->Sum;
        }
    };
    int n, q;
    std::cin >> n >> q;
    auto buf        = std::make_unique<TreapNode[]>(n + q);
    TreapNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::cin >> buf[i].Val;
        root = TreapNode::join(root, &buf[i]);
    }
    for (int i = 0; i < q; ++i) {
        int cmd;
        std::cin >> cmd;
        switch (cmd) {
        case 0: {
            int pos;
            std::cin >> pos >> buf[n + i].Val;
            auto [R0, R1] = TreapNode::split(root, pos);
            root          = TreapNode::join(R0, &buf[n + i], R1);
            break;
        }
        case 1: {
            int pos;
            std::cin >> pos;
            auto [R0, R1, R2] = TreapNode::split(root, pos, 1);
            root              = TreapNode::join(R0, R2);
            break;
        }
        case 2: {
            int l, r;
            std::cin >> l >> r;
            auto [R0, R1, R2] = TreapNode::split(root, l, r - l);
            R1->flip();
            root = TreapNode::join(R0, R1, R2);
            break;
        }
        case 3: {
            int l, r;
            std::cin >> l >> r;
            auto [R0, R1, R2] = TreapNode::split(root, l, r - l);
            std::cin >> R1->Mul >> R1->Add;
            root = TreapNode::join(R0, R1, R2);
            break;
        }
        case 4: {
            int l, r;
            std::cin >> l >> r;
            auto [R0, R1, R2] = TreapNode::split(root, l, r - l);
            std::cout << R1->Sum << '\n';
            root = TreapNode::join(R0, R1, R2);
            break;
        }
        default: break;
        }
    }
    return 0;
}
