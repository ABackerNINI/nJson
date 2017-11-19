//
// Created by nini on 11/5/17.
//
#pragma once

#ifndef _CPP_98_TYPE_TRAITS_H_
#define _CPP_98_TYPE_TRAITS_H_

#if __cplusplus >= 201103L

#include <type_traits>

#else

#define __CONSTEXPR const
#define __NOEXCEPT throw()

//include size_t
#include <stddef.h>

/* This is c++98 type_traits header file.
 * Note 1:Most of these codes are copied from c++11 standard type_traits file.
 * Note 2:Some features can't be supported and are listed below:
 *  template <class _Ty> struct remove_reference<_Ty &&>;
 *  template <class _Ty> struct is_integral<char16_t>;
 *  template <class _Ty> struct is_integral<char32_t>;
 *  template <class Fn, class... ArgTypes> struct result_of<Fn(ArgTypes...)>;
 *  template <class... Types> struct common_type;
 *  template <size_t Len, size_t Align =  default alignment>struct aligned_storage;
 *  template <size_t Len, class... Types> struct aligned_union;
 *  template <class _Ty,class _Uty> constexpr bool is_same_v;
 * */

namespace std {

    // TEMPLATE CLASS integral_constant
    template<class _Ty, _Ty _Val>
    struct integral_constant {// convenient template for integral constant types
        static __CONSTEXPR _Ty value = _Val;

        typedef _Ty value_type;
        typedef integral_constant<_Ty, _Val> type;

        operator __CONSTEXPR value_type() const __NOEXCEPT {
            return (value);
        }

        __CONSTEXPR value_type operator()() const __NOEXCEPT {// return stored value
            return (value);
        }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template<bool _Val>
    struct bool_constant : integral_constant<bool, _Val> {
    };

    // TEMPLATE CLASS _cat_base
    template<bool _Val>
    struct _cat_base : integral_constant<bool, _Val> {// base class for type predicates
    };

    // TEMPLATE CLASS enable_if
    template<bool _Test, class _Ty = void>
    struct enable_if {// type is undefined for assumed !_Test
    };

    template<class _Ty>
    struct enable_if<true, _Ty> {// type is _Ty for _Test
        typedef _Ty type;
    };

    // TEMPLATE CLASS conditional
    template<bool _Test, class _Ty1, class _Ty2>
    struct conditional {// type is _Ty2 for assumed !_Test
        typedef _Ty2 type;
    };

    template<class _Ty1, class _Ty2>
    struct conditional<true, _Ty1, _Ty2> {// type is _Ty1 for _Test
        typedef _Ty1 type;
    };

    // TEMPLATE CLASS is_same
    template<class _Ty1, class _Ty2>
    struct is_same : false_type {// determine whether _Ty1 and _Ty2 are the same type
    };

    template<class _Ty1>
    struct is_same<_Ty1, _Ty1> : true_type {// determine whether _Ty1 and _Ty2 are the same type
    };

    // TEMPLATE CLASS remove_const
    template<class _Ty>
    struct remove_const {// remove top level const qualifier
        typedef _Ty type;
    };

    template<class _Ty>
    struct remove_const<const _Ty> {// remove top level const qualifier
        typedef _Ty type;
    };

    // TEMPLATE CLASS remove_volatile
    template<class _Ty>
    struct remove_volatile {// remove top level volatile qualifier
        typedef _Ty type;
    };

    template<class _Ty>
    struct remove_volatile<volatile _Ty> {// remove top level volatile qualifier
        typedef _Ty type;
    };

    // TEMPLATE CLASS remove_cv
    template<class _Ty>
    struct remove_cv {// remove top level const and volatile qualifiers
        typedef typename remove_const<typename remove_volatile<_Ty>::type>::type type;
    };

    // TEMPLATE CLASS remove_reference
    template<class _Ty>
    struct remove_reference {
        typedef _Ty type;
    };

    template<class _Ty>
    struct remove_reference<_Ty &> {
        typedef _Ty type;
    };

//No "&&" before c++11
//    template<class _Ty>
//    struct remove_reference<_Ty &&> {
//        typedef _Ty type;
//    };

    // TEMPLATE CLASS add_const
    template<class _Ty>
    struct add_const {// add top level const qualifier
        typedef const _Ty type;
    };

    // TEMPLATE CLASS add_volatile
    template<class _Ty>
    struct add_volatile {// add top level volatile qualifier
        typedef volatile _Ty type;
    };

    // TEMPLATE CLASS add_cv
    template<class _Ty>
    struct add_cv {// add top level const and volatile qualifiers
        typedef const volatile _Ty type;
    };

    // TEMPLATE CLASS add_pointer
    template<typename ...>
    struct _void_t {
        typedef void type;
    };

    template<class _Ty, class = void>
    struct _Add_pointer {// add pointer
        typedef _Ty type;
    };

    template<class _Ty>
    struct _Add_pointer<_Ty, typename _void_t<typename remove_reference<_Ty>::type *>::type> {// add pointer
        typedef typename remove_reference<_Ty>::type *type;
    };

    template<class _Ty>
    struct add_pointer {// add pointer
        typedef typename _Add_pointer<_Ty>::type type;
    };

    // TEMPLATE CLASS _is_integral_helper
    template<class _Ty>
    struct _is_integral_helper : false_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<bool> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<char> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<unsigned char> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<signed char> : true_type {// determine whether _Ty is integral
    };

#if(_NATIVE_WCHAR_T_DEFINED /*Windows*/ || _GLIBCXX_USE_WCHAR_T /*Unix*/)
    template<>
    struct _is_integral_helper<wchar_t> : true_type {// determine whether _Ty is integral
    };
#endif

    template<>
    struct _is_integral_helper<unsigned short> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<signed short> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<unsigned int> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<signed int> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<unsigned long> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<signed long> : true_type {// determine whether _Ty is integral
    };

//No char16_t and char32_t before c++11
//    template<>
//    struct _is_integral_helper<char16_t> : true_type {    // determine whether _Ty is integral
//    };
//
//    template<>
//    struct _is_integral_helper<char32_t> : true_type {    // determine whether _Ty is integral
//    };

    template<>
    struct _is_integral_helper<long long> : true_type {// determine whether _Ty is integral
    };

    template<>
    struct _is_integral_helper<unsigned long long> : true_type {// determine whether _Ty is integral
    };

    // TEMPLATE CLASS is_integral
    template<class _Ty>
    struct is_integral : _is_integral_helper<typename remove_cv<_Ty>::type> {// determine whether _Ty is integral
    };

    // TEMPLATE CLASS _is_floating_point_helper
    template<class _Ty>
    struct _is_floating_point_helper : false_type {// determine whether _Ty is floating point
    };

    template<>
    struct _is_floating_point_helper<float> : true_type {// determine whether _Ty is floating point
    };

    template<>
    struct _is_floating_point_helper<double> : true_type {// determine whether _Ty is floating point
    };

    template<>
    struct _is_floating_point_helper<long double> : true_type {// determine whether _Ty is floating point
    };

    // TEMPLATE CLASS is_floating_point
    template<class _Ty>
    struct is_floating_point
            : _is_floating_point_helper<typename remove_cv<_Ty>::type> {// determine whether _Ty is floating point
    };

    // TEMPLATE CLASS is_arithmetic
    template<class _Ty>
    struct is_arithmetic : _cat_base<is_integral<_Ty>::value ||
                                     is_floating_point<_Ty>::value> {// determine whether _Ty is an arithmetic type
    };

    // TEMPLATE CLASS _is_void
    template<class _Ty>
    struct _is_void : false_type {// determine whether _Ty is void
    };

    template<>
    struct _is_void<void> : true_type {// determine whether _Ty is void
    };

    // TEMPLATE CLASS is_void
    template<class _Ty>
    struct is_void : _is_void<typename remove_cv<_Ty>::type> {// determine whether _Ty is void
    };

    // TEMPLATE CLASS is_array
    template<class _Ty>
    struct is_array : false_type {// determine whether _Ty is an array
    };

    template<class _Ty, size_t _Nx>
    struct is_array<_Ty[_Nx]> : true_type {// determine whether _Ty is an array
    };

    template<class _Ty>
    struct is_array<_Ty[]> : true_type {// determine whether _Ty is an array
    };

    // TEMPLATE CLASS _is_signed_base
    template<class _Ty, bool = is_integral<_Ty>::value>
    struct _is_signed_base {// determine whether integral _Ty is a signed or unsigned type
        typedef typename remove_cv<_Ty>::type _Uty;
        typedef _cat_base<_Uty(-1) < _Uty(0)> _Signed;
        typedef _cat_base<_Uty(0) < _Uty(-1)> _Unsigned;
    };

    template<class _Ty>
    struct _is_signed_base<_Ty, false> {// floating-point _Ty is signed
        // non-arithmetic _Ty is neither signed nor unsigned
        typedef is_floating_point<_Ty> _Signed;
        typedef false_type _Unsigned;
    };

    // TEMPLATE CLASS is_signed
    template<class _Ty>
    struct is_signed : _is_signed_base<_Ty>::_Signed {// determine whether _Ty is a signed type
    };

    // TEMPLATE CLASS is_unsigned
    template<class _Ty>
    struct is_unsigned : _is_signed_base<_Ty>::_Unsigned {// determine whether _Ty is an unsigned type
    };
}

#endif //__cplusplus >= 201103L

#endif //_CPP_98_TYPE_TRAITS_H_
