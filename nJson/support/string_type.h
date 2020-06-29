#pragma once

#ifndef _NJSON_SUPPORT_STRING_TYPE_H_
#define _NJSON_SUPPORT_STRING_TYPE_H_

#include <string>
#include "cstr_type.h"

/*
    This file is to support the serialization and deserialization of type
    'std::string'.
*/

template <>
struct njson_support<std::string> {
    static bool is_default(const std::string &njson_var) {
        return njson_var.empty();
    }

    static JSON_Value *serialize(const std::string &njson_var) {
        return njson_support_serialize(njson_var.c_str());
    }

    static void deserialize(JSON_Value *njson_val, std::string *njson_var) {
        const char *s;
        njson_support_deserialize(njson_val, &s);
        if (s) *njson_var = std::string(s);
    }
};

#endif  //_NJSON_SUPPORT_STRING_TYPE_H_
