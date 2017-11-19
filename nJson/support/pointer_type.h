#pragma once

#ifndef _NJSON_SUPPORT_POINTER_TYPE_H_
#define _NJSON_SUPPORT_POINTER_TYPE_H_

#include "support_base.h"

#define NJSON_DEFAULT_VALUE_POINTER NULL

/*
	This file is to support the serialization and deserialization of pointer type.

	Note that you need to implement your own functions to support pointers point to arrays.
	See 'cstr_type.h' for reference.
*/

template<typename T>
struct njson_support<T *> {
    static bool is_default(const T *njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_POINTER || njson_support_is_default(*njson_var);
    }

    static JSON_Value *serialize(const T *njson_var) {
        return njson_support_serialize(*njson_var);
    }

    static void deserialize(JSON_Value *njson_val, T **njson_var) {
        if (*njson_var == NULL)*njson_var = new T();
        njson_support_deserialize(njson_val, *njson_var);
    }
};

#endif//_NJSON_SUPPORT_POINTER_TYPE_H_