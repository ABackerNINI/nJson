#pragma once

#ifndef _NJSON_SUPPORT_CSTR_TYPE_H_
#define _NJSON_SUPPORT_CSTR_TYPE_H_

#include "support_base.h"

/*
	This file is to support the serialization and deserialization of type 'char *'.

	Note that this file support the c-style string end with '/0'.
*/

/*! If you set "NJSON_FEATURE_CONST_CSTR_DUMP 0",please BE ATTENTION to the difference between "char *" and "const char *".
 *  Type "char *" will dump c-string from "JSON_Value" when deserialization while "const char *" not.
 *  So,first,you should free "char *" after using it but keep "const char *".
 *  Second,you should not free "JSON_Value" before using "const char *" got from it.
 * */
#define NJSON_FEATURE_CONST_CSTR_DUMP 1

#define NJSON_DEFAULT_VALUE_CSTR NULL

template<>
struct njson_support<char *> {
    static bool is_default(const char *njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_CSTR;
    }

    static JSON_Value *serialize(const char *njson_var) {
        return json_value_init_string(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, char **njson_var) {
        const char *tmp = json_value_get_string(njson_val);

        if (tmp)*njson_var = strdup(tmp);
    }
};

template<>
struct njson_support<const char *> {
    static bool is_default(const char *njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_CSTR;
    }

    static JSON_Value *serialize(const char *njson_var) {
        return json_value_init_string(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, const char **njson_var) {
#if(NJSON_FEATURE_CONST_CSTR_DUMP)
        const char *tmp = json_value_get_string(njson_val);

        if (tmp)*njson_var = strdup(tmp);
#else
        *njson_var = json_value_get_string(njson_val);
#endif
    }
};

#endif//_NJSON_SUPPORT_CSTR_TYPE_H_