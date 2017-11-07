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
    static bool is_default_value(const T *njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_POINTER || njson_is_default_value(*njson_var);
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const T *njson_var) {
        njson_serialize(njson_val, njson_name, *njson_var);
    }

    static void deserialize(JSON_Value *njson_val, T **njson_var) {
        if (*njson_var == NULL)*njson_var = new T();
        njson_deserialize(njson_val, *njson_var);
    }
};

#endif//_NJSON_SUPPORT_POINTER_TYPE_H_