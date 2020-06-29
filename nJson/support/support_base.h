#pragma once

#ifndef _NJSON_SUPPORT_SUPPORT_BASE_H_
#define _NJSON_SUPPORT_SUPPORT_BASE_H_

#include "../type_traits/type_traits.h"
#include "../parson/parson.h"

template <typename T>
struct njson_support {
    static bool is_default(const T &njson_var) {
        return njson_var.njson_is_default();
    }

    static JSON_Value *serialize(const T &njson_var) {
        return njson_var.njson_serialize();
    }

    static void deserialize(JSON_Value *njson_val, T *njson_var) {
        njson_var->njson_deserialize(njson_val);
    }
};

template <typename T>
bool njson_support_is_default(const T &val) {
    return njson_support<typename std::remove_cv<T>::type>::is_default(val);
}

template <typename T>
JSON_Value *njson_support_serialize(const T &val) {
    return njson_support<typename std::remove_cv<T>::type>::serialize(val);
}

template <typename T>
void njson_support_deserialize(JSON_Value *njson_val, T *njson_var) {
    return njson_support<typename std::remove_cv<T>::type>::deserialize(
        njson_val, njson_var);
}

#endif  //_NJSON_SUPPORT_SUPPORT_BASE_H_
