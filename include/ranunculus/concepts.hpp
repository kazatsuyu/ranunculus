#ifndef RANUNCULUS_CONCEPTS_HPP
#define RANUNCULUS_CONCEPTS_HPP

#include "utility.hpp"

namespace ranunculus {
namespace concepts {

namespace v1 {


template<typename T>
using void_ = enable_when<std::is_void<T>{}>;
template<typename T>
using not_void = enable_when<!std::is_void<T>{}>;
template<typename T>
using null_pointer = enable_when<std::is_null_pointer<T>{}>;
template<typename T>
using not_null_pointer = enable_when<!std::is_null_pointer<T>{}>;
template<typename T>
using integral = enable_when<std::is_integral<T>{}>;
template<typename T>
using not_integral = enable_when<!std::is_integral<T>{}>;
template<typename T>
using floating_point = enable_when<std::is_floating_point<T>{}>;
template<typename T>
using not_floating_point = enable_when<!std::is_floating_point<T>{}>;
template<typename T>
using array = enable_when<std::is_array<T>{}>;
template<typename T>
using not_array = enable_when<!std::is_array<T>{}>;
template<typename T>
using pointer = enable_when<std::is_pointer<T>{}>;
template<typename T>
using not_pointer = enable_when<!std::is_pointer<T>{}>;
template<typename T>
using lvalue_reference = enable_when<std::is_lvalue_reference<T>{}>;
template<typename T>
using not_lvalue_reference = enable_when<!std::is_lvalue_reference<T>{}>;
template<typename T>
using rvalue_reference = enable_when<std::is_rvalue_reference<T>{}>;
template<typename T>
using not_rvalue_reference = enable_when<!std::is_rvalue_reference<T>{}>;
template<typename T>
using member_object_pointer = enable_when<std::is_member_object_pointer<T>{}>;
template<typename T>
using not_member_object_pointer = enable_when<!std::is_member_object_pointer<T>{}>;
template<typename T>
using menber_function_pointer = enable_when<std::is_member_function_pointer<T>{}>;
template<typename T>
using not_menber_function_pointer = enable_when<!std::is_member_function_pointer<T>{}>;
template<typename T>
using enum_ = enable_when<std::is_enum<T>{}>;
template<typename T>
using not_enum = enable_when<!std::is_enum<T>{}>;
template<typename T>
using union_ = enable_when<std::is_union<T>{}>;
template<typename T>
using not_union = enable_when<!std::is_union<T>{}>;
template<typename T>
using class_ = enable_when<std::is_class<T>{}>;
template<typename T>
using not_class = enable_when<!std::is_class<T>{}>;
template<typename T>
using function = enable_when<std::is_function<T>{}>;
template<typename T>
using not_function = enable_when<!std::is_function<T>{}>;

template<typename T>
using reference = enable_when<std::is_reference<T>{}>;
template<typename T>
using not_reference = enable_when<!std::is_reference<T>{}>;
template<typename T>
using arithmetic = enable_when<std::is_arithmetic<T>{}>;
template<typename T>
using not_arithmetic = enable_when<!std::is_arithmetic<T>{}>;
template<typename T>
using fundamental = enable_when<std::is_fundamental<T>{}>;
template<typename T>
using not_fundamental = enable_when<!std::is_fundamental<T>{}>;
template<typename T>
using object = enable_when<std::is_object<T>{}>;
template<typename T>
using not_object = enable_when<!std::is_object<T>{}>;
template<typename T>
using scalar = enable_when<std::is_scalar<T>{}>;
template<typename T>
using not_scalar = enable_when<!std::is_scalar<T>{}>;
template<typename T>
using compound = enable_when<std::is_compound<T>{}>;
template<typename T>
using not_compound = enable_when<!std::is_compound<T>{}>;
template<typename T>
using member_pointer = enable_when<std::is_member_pointer<T>{}>;
template<typename T>
using not_member_pointer = enable_when<!std::is_member_pointer<T>{}>;

template<typename T>
using const_ = enable_when<std::is_const<T>{}>;
template<typename T>
using not_const = enable_when<!std::is_const<T>{}>;
template<typename T>
using volatile_ = enable_when<std::is_volatile<T>{}>;
template<typename T>
using not_volatile = enable_when<!std::is_volatile<T>{}>;
template<typename T>
using trivial = enable_when<std::is_trivial<T>{}>;
template<typename T>
using not_trivial = enable_when<!std::is_trivial<T>{}>;
template<typename T>
using torivialloy_copyable = enable_when<std::is_trivially_copyable<T>{}>;
template<typename T>
using not_torivialloy_copyable = enable_when<!std::is_trivially_copyable<T>{}>;
template<typename T>
using standard_layout = enable_when<std::is_standard_layout<T>{}>;
template<typename T>
using not_standard_layout = enable_when<!std::is_standard_layout<T>{}>;
template<typename T>
using pod = enable_when<std::is_pod<T>{}>;
template<typename T>
using not_pod = enable_when<!std::is_pod<T>{}>;
template<typename T>
using literal_type = enable_when<std::is_literal_type<T>{}>;
template<typename T>
using not_literal_type = enable_when<!std::is_literal_type<T>{}>;
template<typename T>
using empty = enable_when<std::is_empty<T>{}>;
template<typename T>
using not_empty = enable_when<!std::is_empty<T>{}>;
template<typename T>
using polymorphic = enable_when<std::is_polymorphic<T>{}>;
template<typename T>
using not_polymorphic = enable_when<!std::is_polymorphic<T>{}>;
template<typename T>
using abstract = enable_when<std::is_abstract<T>{}>;
template<typename T>
using not_abstract = enable_when<!std::is_abstract<T>{}>;
template<typename T>
using final_ = enable_when<std::is_final<T>{}>;
template<typename T>
using not_final = enable_when<!std::is_final<T>{}>;
template<typename T>
using signed_ = enable_when<std::is_signed<T>{}>;
template<typename T>
using not_signed = enable_when<!std::is_signed<T>{}>;
template<typename T>
using unsigned_ = enable_when<std::is_unsigned<T>{}>;
template<typename T>
using not_unsigned = enable_when<!std::is_unsigned<T>{}>;
template<typename T, typename ...TA>
using constructible = enable_when<std::is_constructible<T, TA...>{}>;
template<typename T, typename ...TA>
using not_constructible = enable_when<!std::is_constructible<T, TA...>{}>;
template<typename T>
using default_constructible = enable_when<std::is_default_constructible<T>{}>;
template<typename T>
using not_default_constructible = enable_when<!std::is_default_constructible<T>{}>;
template<typename T>
using copy_constructible = enable_when<std::is_copy_constructible<T>{}>;
template<typename T>
using not_copy_constructible = enable_when<!std::is_copy_constructible<T>{}>;
template<typename T>
using move_constructible = enable_when<std::is_move_constructible<T>{}>;
template<typename T>
using not_move_constructible = enable_when<!std::is_move_constructible<T>{}>;
template<typename T, typename ...TA>
using assignable = enable_when<std::is_assignable<T, TA...>{}>;
template<typename T, typename ...TA>
using not_assignable = enable_when<!std::is_assignable<T, TA...>{}>;
template<typename T>
using copy_assignable = enable_when<std::is_copy_assignable<T>{}>;
template<typename T>
using not_copy_assignable = enable_when<!std::is_copy_assignable<T>{}>;
template<typename T>
using move_assignable = enable_when<std::is_move_assignable<T>{}>;
template<typename T>
using not_move_assignable = enable_when<!std::is_move_assignable<T>{}>;
template<typename T>
using destructible = enable_when<std::is_destructible<T>{}>;
template<typename T>
using not_destructible = enable_when<!std::is_destructible<T>{}>;
template<typename T, typename ...TA>
using trivially_constructible = enable_when<std::is_trivially_constructible<T, TA...>{}>;
template<typename T, typename ...TA>
using not_trivially_constructible = enable_when<!std::is_trivially_constructible<T, TA...>{}>;
template<typename T>
using trivially_default_constructible = enable_when<std::is_trivially_default_constructible<T>{}>;
template<typename T>
using not_trivially_default_constructible = enable_when<!std::is_trivially_default_constructible<T>{}>;
template<typename T>
using trivially_copy_constructible = enable_when<std::is_trivially_copy_constructible<T>{}>;
template<typename T>
using not_trivially_copy_constructible = enable_when<!std::is_trivially_copy_constructible<T>{}>;
template<typename T, typename ...TA>
using trivially_assignable = enable_when<std::is_trivially_assignable<T, TA...>{}>;
template<typename T, typename ...TA>
using not_trivially_assignable = enable_when<!std::is_trivially_assignable<T, TA...>{}>;
template<typename T>
using trivially_copy_assignable = enable_when<std::is_trivially_copy_assignable<T>{}>;
template<typename T>
using not_trivially_copy_assignable = enable_when<!std::is_trivially_copy_assignable<T>{}>;
template<typename T>
using trivially_move_assignable = enable_when<std::is_trivially_move_assignable<T>{}>;
template<typename T>
using not_trivially_move_assignable = enable_when<!std::is_trivially_move_assignable<T>{}>;
template<typename T>
using trivially_destructible = enable_when<std::is_trivially_destructible<T>{}>;
template<typename T>
using not_trivially_destructible = enable_when<!std::is_trivially_destructible<T>{}>;
template<typename T, typename ...TA>
using nothrow_constructible = enable_when<std::is_nothrow_constructible<T, TA...>{}>;
template<typename T, typename ...TA>
using not_nothrow_constructible = enable_when<!std::is_nothrow_constructible<T, TA...>{}>;
template<typename T>
using nothrow_default_constructible = enable_when<std::is_nothrow_default_constructible<T>{}>;
template<typename T>
using throw_default_constructible = enable_when<!std::is_nothrow_default_constructible<T>{}>;
template<typename T>
using nothrow_copy_constructible = enable_when<std::is_nothrow_copy_constructible<T>{}>;
template<typename T>
using throw_copy_constructible = enable_when<!std::is_nothrow_copy_constructible<T>{}>;
template<typename T, typename ...TA>
using nothrow_assignable = enable_when<std::is_nothrow_assignable<T, TA...>{}>;
template<typename T, typename ...TA>
using throw_assignable = enable_when<!std::is_nothrow_assignable<T, TA...>{}>;
template<typename T>
using nothrow_copy_assignable = enable_when<std::is_nothrow_copy_assignable<T>{}>;
template<typename T>
using throw_copy_assignable = enable_when<!std::is_nothrow_copy_assignable<T>{}>;
template<typename T>
using nothrow_move_assignable = enable_when<std::is_nothrow_move_assignable<T>{}>;
template<typename T>
using throw_move_assignable = enable_when<!std::is_nothrow_move_assignable<T>{}>;
template<typename T>
using nothrow_destructible = enable_when<std::is_nothrow_destructible<T>{}>;
template<typename T>
using throw_destructible = enable_when<!std::is_nothrow_destructible<T>{}>;
template<typename T>
using virtual_destructor = enable_when<std::has_virtual_destructor<T>{}>;
template<typename T>
using not_virtual_destructor = enable_when<!std::has_virtual_destructor<T>{}>;

template<typename T, typename U>
using same = enable_when<std::is_same<T, U>{}>;
template<typename T, typename U>
using not_same = enable_when<!std::is_same<T, U>{}>;
template<typename T, typename U>
using base_of = enable_when<std::is_base_of<T, U>{}>;
template<typename T, typename U>
using not_base_of = enable_when<!std::is_base_of<T, U>{}>;
template<typename T, typename U>
using convertible = enable_when<std::is_convertible<T, U>{}>;
template<typename T, typename U>
using not_convertible = enable_when<!std::is_convertible<T, U>{}>;

}

using namespace v1;

} //namespace concepts
} //namespace ranunculus

#endif

