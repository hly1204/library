#ifndef PAIRING_HEAP_HEADER_HPP
#define PAIRING_HEAP_HEADER_HPP

/**
 * @brief pairing heap
 *
 */

#include <utility>

namespace lib {

template <typename Type, typename Comp>
class PairingHeap {
public:
  struct Node {
    Node *c, *s, *p; // first_child, sibling, parent
    Type it;
    Node(const Type &it) : c(nullptr), s(nullptr), p(nullptr), it(it) {}
    ~Node() {
      delete s;
      delete c;
    }
  };

  using node_type           = Node;
  using node_ptr_type       = Node *;
  using const_node_ptr_type = const Node *;

  PairingHeap(Comp cmp) : rt_(nullptr), cmp_(cmp) {}
  PairingHeap() : PairingHeap(Comp()) {}
  PairingHeap(const PairingHeap &rhs) = delete;
  ~PairingHeap() { delete rt_; }

  PairingHeap &operator=(const PairingHeap &rhs) = delete; // 赋值和复制构造都不实现
  PairingHeap &meld(PairingHeap &h) {
    if (&h != this) rt_ = meld(rt_, h.rt_), h.rt_ = nullptr;
    return *this;
  }
  const Node *insert(const Type &it) {
    Node *r = new Node(it);
    rt_     = meld(rt_, r);
    return const_cast<const Node *>(r);
  }
  bool is_empty() const { return rt_ == nullptr; }
  Type find_min() const { return rt_->it; }
  void delete_min() {
    Node *r = rt_;
    if (r->c != nullptr) {
      r->c->p = nullptr;
      rt_     = pair(r->c);
      r->c    = nullptr;
    } else {
      rt_ = nullptr;
    }
    delete r;
  }
  void delete_arbitrary(const Node *x) {
    if (x->p == nullptr) return delete_min();
    Node *y = const_cast<Node *>(x);
    cut(y);
    Node *t = y->c;
    if (t != nullptr) y->c = t->p = nullptr;
    delete y;
    meld(pair(t), rt_);
  }
  void decrease_key(const Node *x, const Type &it) { // 必须在该堆内
    if (x == rt_) {
      rt_->it = it;
    } else {
      Node *y = const_cast<Node *>(x);
      cut(y);
      y->it = it;
      rt_   = meld(rt_, y);
    }
  }

private:
  Node *rt_;
  Comp cmp_;

  static void cut(Node *x) {
    if (x->p != nullptr) {
      if ((((x->p->c == x) ? x->p->c : x->p->s) = x->s) != nullptr) {
        x->s->p = x->p;
        x->s    = nullptr;
      }
      x->p = nullptr;
    }
  }
  Node *meld(Node *x, Node *y) { // x, y 为不同的根
    if (x == nullptr) return y;
    if (y == nullptr) return x;
    if (cmp_(y->it, x->it)) std::swap(x, y); // 使 x->it <= y->it
    if ((y->s = x->c) != nullptr) x->c->p = y;
    return (x->c = y)->p = x;
  }
  Node *pair(Node *x) { // 从右往左配对，论文中有其他变种，但有些时间复杂度不明确
    if (x == nullptr || x->s == nullptr) return x;
    Node *y = x->s, *z = y->s;
    x->s = y->p = y->s = nullptr;
    if (z != nullptr) z->p = nullptr;
    return meld(pair(z), meld(x, y));
  }
};

} // namespace lib

#endif