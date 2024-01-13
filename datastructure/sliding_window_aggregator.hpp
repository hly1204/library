#ifndef SLIDING_WINDOW_AGGREGATOR_HPP
#define SLIDING_WINDOW_AGGREGATOR_HPP

#include "../common.hpp"

#include <cassert>
#include <functional>
#include <optional>
#include <stack>
#include <utility>
#include <vector>

LIB_BEGIN

// see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf
template <typename T, typename OpT>
class sliding_window_aggregator {
  OpT f_ = {};
  std::stack<T, std::vector<T>> front_, back_;
  std::optional<T> back_agg_;

public:
  sliding_window_aggregator() = default;
  explicit sliding_window_aggregator(OpT op) : f_(op) {}
  void push(const T &v) { push_back(v); }
  void pop() { pop_front(); }
  auto size() const { return front_.size() + back_.size(); }
  bool empty() const { return front_.empty() && back_.empty(); }
  void push_back(const T &v) {
    back_.push(v);
    if (back_agg_) {
      back_agg_.emplace(std::invoke(f_, *back_agg_, v));
    } else {
      back_agg_.emplace(v);
    }
  }

  void pop_front() {
    assert(!empty());
    if (front_.empty()) {
      front_.push(back_.top());
      back_.pop();
      while (!back_.empty()) {
        front_.push(std::invoke(f_, back_.top(), front_.top()));
        back_.pop();
      }
      back_agg_.reset();
    }
    front_.pop();
  }

  std::optional<T> query() const {
    if (empty()) return {};
    if (front_.empty()) return back_agg_;
    if (!back_agg_) return front_.top();
    return std::invoke(f_, front_.top(), *back_agg_);
  }
};

template <typename T, typename OpT>
using swag = sliding_window_aggregator<T, OpT>;

LIB_END

#endif
