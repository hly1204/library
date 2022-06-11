#ifndef MIN_HEIGHT_BASED_LEFTIST_TREE_HPP
#define MIN_HEIGHT_BASED_LEFTIST_TREE_HPP

#include "../common.hpp"

#include <cassert>
#include <cstdint>
#include <functional>
#include <iterator>
#include <queue>
#include <type_traits>
#include <utility>

LIB_BEGIN

template <typename T, typename CmpT = std::less<>>
class min_height_based_leftist_tree {
  static_assert(std::is_copy_constructible_v<T>);

  class node {
  public:
    node *left_{}, *right_{}, *parent_{};
    int rank_{1}; // a.k.a. s value
    T value_;
    node(const T &value) : value_(value) {}
    ~node() {
      delete left_;
      delete right_;
    }
  } * root_{};
  CmpT cmp_;
  std::size_t size_{};

  static std::size_t s(node *a) { return a ? a->rank_ : 0; }

  node *meld(node *a, node *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (!cmp_(a->value_, b->value_)) std::swap(a, b);
    if (a->right_) a->right_->parent_ = nullptr;
    if (((a->right_ = meld(a->right_, b))->parent_ = a)->left_ == nullptr ||
        a->left_->rank_ < a->right_->rank_)
      std::swap(a->left_, a->right_);
    a->rank_ = s(a->right_) + 1;
    return a;
  }

public:
  using value_type       = T;
  using pointer          = node *;
  using const_pointer    = const node *;
  using size_type        = std::size_t;
  using signed_size_type = std::make_signed_t<std::size_t>;

  class wrapper {
    const node *p_{};

  public:
    wrapper() = default;
    wrapper(const node *p) : p_(p) {}
    const T &operator*() const { return *p_; }
    const node *data() const { return p_; }
  };

  min_height_based_leftist_tree(CmpT cmp = CmpT()) : cmp_(cmp) {}
  template <
      typename IterT,
      std::enable_if_t<std::is_convertible_v<typename std::iterator_traits<IterT>::value_type, T>,
                       int> = 0>
  min_height_based_leftist_tree(IterT begin, IterT end, CmpT cmp = CmpT())
      : cmp_(cmp), size_(end - begin) {
    std::queue<node *> q;
    for (; begin != end; ++begin) q.push(new node(*begin));
    while (q.size() > 1) {
      node *a = q.front();
      q.pop();
      node *b = q.front();
      q.pop();
      q.push(meld(a, b));
    }
    if (!q.empty()) root_ = q.front();
  }
  min_height_based_leftist_tree(const min_height_based_leftist_tree &) = delete;
  ~min_height_based_leftist_tree() { delete root_; }
  min_height_based_leftist_tree &operator=(const min_height_based_leftist_tree &) = delete;

  bool empty() const { return root_ == nullptr; }
  std::size_t size() const { return size_; }
  std::make_signed_t<std::size_t> ssize() const { return size_; }
  wrapper insert(const T &value) {
    node *p = new node(value);
    root_   = meld(root_, p);
    ++size_;
    return wrapper(p);
  }
  T find_min() const { return root_->value_; }
  T extract(wrapper wp); // TODO
  T extract_min() {
    assert(!empty());
    node *p = root_;
    T res(p->value_);
    if (p->left_) {
      p->left_->parent_ = nullptr;
      if (p->right_) p->right_->parent_ = nullptr;
    }
    root_    = meld(p->left_, p->right_);
    p->left_ = p->right_ = nullptr;
    delete p;
    --size_;
    return res;
  }
};

template <typename T, typename CmpT>
using min_hblt = min_height_based_leftist_tree<T, CmpT>;

LIB_END

#endif