#pragma once

#include <cassert>
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace detail {

template<int N> inline unsigned long long from_bit_string(const char *s) {
    return from_bit_string<N / 2>(s + N / 2) << (N / 2) | from_bit_string<N / 2>(s);
}

template<> inline unsigned long long from_bit_string<1>(const char *s) { return s[0] == '1'; }

template<int N> inline void to_bit_string(unsigned long long v, char *s) {
    to_bit_string<N / 2>(v, s);
    to_bit_string<N / 2>(v >> (N / 2), s + N / 2);
}

template<> inline void to_bit_string<1>(unsigned long long v, char *s) { s[0] = ((v & 1) + '0'); }

} // namespace detail

// TODO: operator<< operator>> ...
class BitArray {
public:
    using ULL                          = unsigned long long;
    static constexpr std::size_t WIDTH = sizeof(ULL) * 8;
    std::vector<ULL> D;
    std::size_t S;

    BitArray() : S() {}
    explicit BitArray(std::size_t L) : D(get_size(L)), S(L) {}
    explicit BitArray(std::string s) : D(get_size(s.size())), S(s.size()) {
        s.resize(get_size(S) * WIDTH);
        for (std::size_t i = 0; i < s.size(); i += WIDTH)
            D[i / WIDTH] = detail::from_bit_string<WIDTH>(s.data() + i);
    }

    void swap(BitArray &other) {
        D.swap(other.D);
        std::swap(S, other.S);
    }

private:
    static std::size_t get_size(std::size_t L) {
        if (L == 0) return 0;
        return (L - 1) / WIDTH + 1;
    }

public:
    [[nodiscard]] std::size_t size() const { return S; }
    [[nodiscard]] std::make_signed_t<std::size_t> ssize() const { return S; }

    void resize(std::size_t L, bool v = false) {
        D.resize(get_size(L));
        if (L > S) {
            if (S % WIDTH != 0)
                if (const std::size_t SS = get_size(S)) D[SS - 1] &= (1ULL << (S % WIDTH)) - 1;
            if (v)
                for (std::size_t i = get_size(S); i < D.size(); ++i) D[i] = ~0ULL;
        }
        S = L;
    }

    void clear() {
        D.clear();
        S = 0;
    }

    void assign(std::size_t L, bool v) { D.assign(get_size(L), v ? ~0ULL : 0ULL); }

    BitArray &set() {
        for (std::size_t i = 0; i < D.size(); ++i) D[i] = ~0ULL;
        return *this;
    }

    BitArray &set(std::size_t P, bool v = true) {
        if (v) {
            D[P / WIDTH] |= 1ULL << (P % WIDTH);
        } else {
            D[P / WIDTH] &= ~(1ULL << (P % WIDTH));
        }
        return *this;
    }

    BitArray &reset() {
        for (std::size_t i = 0; i < D.size(); ++i) D[i] = 0ULL;
        return *this;
    }

    BitArray &reset(std::size_t P) {
        D[P / WIDTH] &= ~(1ULL << (P % WIDTH));
        return *this;
    }

    BitArray &flip() {
        for (std::size_t i = 0; i < D.size(); ++i) D[i] = ~D[i];
        return *this;
    }

    BitArray &flip(std::size_t P) {
        D[P / WIDTH] ^= 1ULL << (P % WIDTH);
        return *this;
    }

    [[nodiscard]] bool test(std::size_t P) const { return D[P / WIDTH] >> (P % WIDTH) & 1; }

    [[nodiscard]] bool all() const {
        if (S == 0) return true;
        if (D.size() > 1) {
            for (std::size_t i = 0; i < D.size() - 1; ++i)
                if (~D[i] != 0) return false;
        }
        return (~D.back() & ((1ULL << (S % WIDTH)) - 1)) == 0;
    }
    [[nodiscard]] bool any() const {
        if (S == 0) return true;
        if (D.size() > 1) {
            for (std::size_t i = 0; i < D.size() - 1; ++i)
                if (D[i] != 0) return true;
        }
        return (D.back() & ((1ULL << (S % WIDTH)) - 1)) != 0;
    }
    [[nodiscard]] bool none() const {
        if (S == 0) return true;
        return !any();
    }

    class Proxy {
        friend BitArray;
        std::vector<ULL>::iterator I;
        unsigned O;

        Proxy(std::vector<ULL>::iterator I, unsigned O) : I(I), O(O) {}

    public:
        Proxy &operator=(bool v) {
            v ? (*I |= 1ULL << O) : (*I &= ~(1ULL << O));
            return *this;
        }
        operator bool() const { return *I & (1ULL << O); }
    };

    class ConstProxy {
        friend BitArray;
        std::vector<ULL>::const_iterator I;
        unsigned O;

        ConstProxy(std::vector<ULL>::const_iterator I, unsigned O) : I(I), O(O) {}

    public:
        ConstProxy(const Proxy &P) : I(P.I), O(P.O) {}
        operator bool() const { return *I & (1ULL << O); }
    };

    [[nodiscard]] Proxy operator[](std::size_t P) {
        return Proxy(D.begin() + P / WIDTH, P % WIDTH);
    }
    [[nodiscard]] Proxy at(std::size_t P) {
        assert(P < S);
        return operator[](P);
    }

    [[nodiscard]] ConstProxy operator[](std::size_t P) const {
        return ConstProxy(D.begin() + P / WIDTH, P % WIDTH);
    }
    [[nodiscard]] ConstProxy at(std::size_t P) const {
        assert(P < S);
        return operator[](P);
    }

    BitArray &operator&=(const BitArray &R) {
        assert(S == R.S);
        for (std::size_t i = 0; i < D.size(); ++i) D[i] &= R.D[i];
        return *this;
    }

    BitArray &operator|=(const BitArray &R) {
        assert(S == R.S);
        for (std::size_t i = 0; i < D.size(); ++i) D[i] |= R.D[i];
        return *this;
    }

    BitArray &operator^=(const BitArray &R) {
        assert(S == R.S);
        for (std::size_t i = 0; i < D.size(); ++i) D[i] ^= R.D[i];
        return *this;
    }

    [[nodiscard]] std::string to_string() const {
        std::string res(D.size() * WIDTH, 0);
        char *d = res.data();
        for (std::size_t i = 0; i < D.size(); ++i)
            detail::to_bit_string<WIDTH>(D[i], d + i * WIDTH);
        res.resize(S);
        return res;
    }

    friend BitArray operator&(const BitArray &L, const BitArray &R) { return BitArray(L) &= R; }
    friend BitArray operator|(const BitArray &L, const BitArray &R) { return BitArray(L) |= R; }
    friend BitArray operator^(const BitArray &L, const BitArray &R) { return BitArray(L) ^= R; }
};
