#ifndef MODINT_TRAITS_HEADER_HPP
#define MODINT_TRAITS_HEADER_HPP

/**
 * @brief modint traits
 *
 */

namespace lib {

template <typename mod_t>
struct modint_traits {
  using type = typename mod_t::value_type;
  static constexpr type get_mod() { return mod_t::get_mod(); }
  static constexpr type get_primitive_root_prime() { return mod_t::get_primitive_root_prime(); }
};

} // namespace lib

#endif