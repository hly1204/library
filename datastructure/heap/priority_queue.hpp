#ifndef PRIORITY_QUEUE_HEADER_HPP
#define PRIORITY_QUEUE_HEADER_HPP

/**
 * @brief priority queue / 优先队列
 *
 */

#include <functional>

#include "pairing_heap.hpp"

namespace lib {

template <typename Type, typename Comp = std::less<>, typename Container = PairingHeap<Type, Comp>>
class PriorityQueue {
public:
  using node_type           = typename Container::node_type;
  using node_ptr_type       = typename Container::node_ptr_type;
  using const_node_ptr_type = typename Container::const_node_ptr_type;

  PriorityQueue(Comp cmp) : heap_(new Container(cmp)), sz_(0) {}
  PriorityQueue() : PriorityQueue(Comp()) {}
  ~PriorityQueue() { delete heap_; }

  PriorityQueue(const PriorityQueue &) = delete;
  PriorityQueue &operator=(const PriorityQueue &) = delete;

  int size() const { return sz_; }
  bool is_empty() const { return sz_ == 0; }

  const_node_ptr_type insert(const Type &it) {
    ++sz_;
    return heap_->insert(it);
  }
  void delete_min() {
    if (is_empty()) return;
    --sz_;
    heap_->delete_min();
  }
  Type find_min() const { return heap_->find_min(); }
  void decrease_key(const_node_ptr_type n, const Type &new_key) { heap_->decrease_key(n, new_key); }
  void delete_arbitrary(const_node_ptr_type n) {
    --sz_;
    heap_->delete_arbitrary(n);
  }

private:
  Container *heap_;
  int sz_;
};

} // namespace lib

#endif