#ifndef BINARY_TRIE_HPP
#define BINARY_TRIE_HPP

#include "../common.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <type_traits>

LIB_BEGIN

template <int BitT>
class binary_trie {
  class node {
  public:
    node *ch_[2]{};
    int cnt_{};
    ~node() {
      delete ch_[0];
      delete ch_[1];
    }
    bool is_leaf() const { return ch_[0] == ch_[1]; }
  };

  mutable std::array<node *, BitT + 1> s_;

public:
  static_assert(BitT > 0 && BitT <= 64);
  using value_type = std::conditional_t<BitT <= 32, std::uint32_t, std::uint64_t>;

  binary_trie() { s_.back() = new node; }
  ~binary_trie() { delete s_.back(); }

  bool empty() const { return s_.back()->ch_[0] == s_.back()->ch_[1]; }

  void insert(value_type a) {
    auto c = s_.back();
    for (int i = BitT - 1; i >= 0; --i) {
      auto j = (a >> i) & 1;
      if (c->ch_[j] == nullptr) c->ch_[j] = new node;
      c = c->ch_[j];
    }
    ++c->cnt_;
  }

  bool contains(value_type a) const {
    for (int i = BitT - 1; i >= 0; --i)
      if ((s_[i] = s_[i + 1]->ch_[(a >> i) & 1]) == nullptr) return false;
    return true;
  }

  bool erase(value_type a) {
    if (!contains(a)) return false;
    --s_.front()->cnt_;
    for (int i = 0; i != BitT; ++i) {
      if (s_[i]->cnt_ || !s_[i]->is_leaf()) break;
      auto p                             = s_[i + 1];
      p->ch_[p->ch_[0] == s_[i] ? 0 : 1] = nullptr;
      delete s_[i];
    }
    return true;
  }

  value_type xor_max(value_type a) const {
    assert(!empty());
    value_type r = 0;
    auto c       = s_.back();
    for (int i = BitT - 1; i >= 0; --i) {
      auto j = (a >> i) & 1;
      r <<= 1;
      if (c->ch_[j ^ 1] != nullptr) {
        c = c->ch_[j ^ 1], r |= 1;
      } else {
        c = c->ch_[j];
      }
    }
    return r;
  }

  value_type xor_min(value_type a) const {
    assert(!empty());
    value_type r = 0;
    auto c       = s_.back();
    for (int i = BitT - 1; i >= 0; --i) {
      auto j = (a >> i) & 1;
      r <<= 1;
      if (c->ch_[j] != nullptr) {
        c = c->ch_[j];
      } else {
        c = c->ch_[j ^ 1], r |= 1;
      }
    }
    return r;
  }
};

LIB_END

#endif
