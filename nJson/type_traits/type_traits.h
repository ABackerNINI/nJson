//
// Created by nini on 11/5/17.
//

#ifndef _CPP_98_TYPE_TRAITS_H_
#define _CPP_98_TYPE_TRAITS_H_

#if __cplusplus >= 201103L

#include <type_traits>

#else

namespace std {

    // TEMPLATE CLASS integral_constant
    template<class _Ty, _Ty _Val>
    struct integral_constant {// convenient template for integral constant types
        static const _Ty value = _Val;

        typedef _Ty value_type;
        typedef integral_constant<_Ty, _Val> type;

        operator const value_type() const {
            return (value);
        }

        const value_type operator()() const {// return stored value
            return (value);
        }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

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
    struct remove_cv {    // remove top level const and volatile qualifiers
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

//No && before c++11
//    template<class _Ty>
//    struct remove_reference<_Ty &&> {
//        typedef _Ty type;
//    };

    // TEMPLATE CLASS is_same
    template<class _Ty1, class _Ty2>
    struct is_same : false_type {// determine whether _Ty1 and _Ty2 are the same type
    };

    template<class _Ty1>
    struct is_same<_Ty1, _Ty1> : true_type {// determine whether _Ty1 and _Ty2 are the same type
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

    // TEMPLATE CLASS _sign_base
    template<class _Ty, bool = is_integral<_Ty>::value>
    struct _sign_base {// determine whether integral _Ty is a signed or unsigned type
        typedef typename remove_cv<_Ty>::type _Uty;
        typedef _cat_base<_Uty(-1) < _Uty(0)> _Signed;
        typedef _cat_base<_Uty(0) < _Uty(-1)> _Unsigned;
    };

    template<class _Ty>
    struct _sign_base<_Ty, false> {// floating-point _Ty is signed
        // non-arithmetic _Ty is neither signed nor unsigned
        typedef is_floating_point<_Ty> _Signed;
        typedef false_type _Unsigned;
    };

    // TEMPLATE CLASS is_signed
    template<class _Ty>
    struct is_signed : _sign_base<_Ty>::_Signed {// determine whether _Ty is a signed type
    };

    // TEMPLATE CLASS is_unsigned
    template<class _Ty>
    struct is_unsigned : _sign_base<_Ty>::_Unsigned {// determine whether _Ty is an unsigned type
    };
}

#endif

#endif //_CPP_98_TYPE_TRAITS_H_
