#pragma once

#include <type_traits>

template <typename Tp, typename Op,
          std::enable_if_t<std::is_invocable_r_v<Tp, Op, const Tp &, const Tp &>, int> = 0>
class Monoid {
public:
    Op F;
    Tp Id;

    explicit Monoid(Op F, const Tp &Id = {}) : F(F), Id(Id) {}

    const Tp &id() const { return Id; }
    Tp operator()(const Tp &L, const Tp &R) const { return F(L, R); }
};
