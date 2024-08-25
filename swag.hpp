#pragma once

#include <cstddef>
#include <optional>
#include <stack>
#include <type_traits>
#include <vector>

// see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf
template <typename Tp, typename Op,
          std::enable_if_t<std::is_invocable_r_v<Tp, Op, const Tp &, const Tp &>, int> = 0>
class SWAG {
public:
    Op F;
    std::stack<Tp, std::vector<Tp>> Front, Back;
    std::optional<Tp> Agg;

    explicit SWAG(Op F) : F(F) {}
    bool empty() const { return Front.empty() && Back.empty(); }
    std::size_t size() const { return Front.size() + Back.size(); }
    void push_back(const Tp &v) {
        Back.push(v);
        Agg.emplace(Agg ? F(*Agg, v) : v);
    }
    void pop_front() {
        assert(!empty());
        if (Front.empty()) {
            Front.push(Back.top());
            Back.pop();
            while (!Back.empty()) {
                Front.push(F(Back.top(), Front.top()));
                Back.pop();
            }
            Agg.reset();
        }
        Front.pop();
    }

    // returns F(Q[0],F(...,F(Q[N-2],Q[N-1]))
    std::optional<Tp> query() const {
        if (empty()) return {};
        if (Front.empty()) return Agg;
        if (!Agg) return Front.top();
        return F(Front.top(), *Agg);
    }
};
