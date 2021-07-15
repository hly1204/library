#ifndef TYPE_TRAITS_HEADER_HPP
#define TYPE_TRAITS_HEADER_HPP

/**
 * @brief type traits / 类型萃取
 *
 */

#include <cstdint>
#include <type_traits>

namespace lib {

template <typename Type>
struct promote_integral;
template <>
struct promote_integral<std::int32_t> {
  using type = std::int64_t;
};
template <>
struct promote_integral<std::uint32_t> {
  using type = std::uint64_t;
};

// 辅助模板
template <typename Type>
using promote_integral_t = typename promote_integral<Type>::type;

template <typename T, typename U>
using longer_integral_t =
    std::conditional_t<(sizeof(T) > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>)),
                       T, U>;

} // namespace lib

#endif
