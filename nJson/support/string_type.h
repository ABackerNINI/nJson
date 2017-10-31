#pragma once

#ifndef _NJSON_SUPPORT_STRING_TYPE_H_
#define _NJSON_SUPPORT_STRING_TYPE_H_

#include <string>
#include "cstr_type.h"

/*
	This file is to support the serialization and deserialization of type 'std::string'.
*/

inline bool njson_is_default_value(const std::string &njson_var);

inline JSON_Value *njson_serialize(const std::string &njson_var);

inline void njson_deserialize(JSON_Value *njson_val, std::string *njson_var);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool njson_is_default_value(const std::string &njson_var) {
    return njson_var.size() == 0;
}

inline JSON_Value *njson_serialize(const std::string &njson_var) {
    return njson_serialize(njson_var.c_str());
}

inline void njson_deserialize(JSON_Value *njson_val, std::string *njson_var) {
    const char *s;
    njson_deserialize(njson_val, &s);
    if (s)*njson_var = std::string(s);
}

#endif//_NJSON_SUPPORT_STRING_TYPE_H_