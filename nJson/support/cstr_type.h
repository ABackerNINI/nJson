#pragma once

#ifndef _NJSON_SUPPORT_CSTR_TYPE_H_
#define _NJSON_SUPPORT_CSTR_TYPE_H_

#include "support_base.h"

/*
	This file is to support the serialization and deserialization of type 'char *'.

	Note that this file support the c-style string end with '/0'.
*/

/*! Be attention to the difference between "char *" and "const char *".
 *  Type "char *" will dump c-string from "JSON_Value" when deserialization while "const char *" not.
 *  So,first,you should free "char *" after using it but keep "const char *".
 *  Second,you should not free "JSON_Value" before using "const char *" got from it.
 * */

#define NJSON_DEFAULT_VALUE_CSTR NULL

template<>
struct njson_support<char *> {
    static bool is_default_value(const char *njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_CSTR;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const char *njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_string(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, char **njson_var) {
        const char *tmp = json_value_get_string(njson_val);

        if (tmp)*njson_var = strdup(tmp);
    }
};

template<>
struct njson_support<const char *> {
    static bool is_default_value(const char *njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_CSTR;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const char *njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_string(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, const char **njson_var) {
        ////TODO:test
        *njson_var = json_value_get_string(njson_val);
    }
};

#endif//_NJSON_SUPPORT_CSTR_TYPE_H_