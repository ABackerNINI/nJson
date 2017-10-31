#pragma once

#ifndef _NJSON_SUPPORT_CSTR_TYPE_H_
#define _NJSON_SUPPORT_CSTR_TYPE_H_

#include <memory.h>
#include "../parson/parson.h"

/*
	This file is to support the serialization and deserialization of type 'char *'.
	Note that this file support the c-style string end with '/0'.
*/

/*Feature 'strdup' will malloc and copy c-style strings from json-object,
  that means you need to free it manually afterwards.*/
#define FEATURE_STRDUP 1

#define NJSON_DEFAULT_VALUE_CSTR NULL

inline bool njson_is_default_value(const char *njson_var);

inline JSON_Value *njson_serialize(const char *&njson_var);

inline void njson_deserialize(JSON_Value *njson_val, const char **njson_var);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool njson_is_default_value(const char *njson_var) {
    return njson_var == NJSON_DEFAULT_VALUE_CSTR;
}

inline JSON_Value *njson_serialize(const char *&njson_var) {
    return json_value_init_string(njson_var);
}

inline void njson_deserialize(JSON_Value *njson_val, const char **njson_var) {
    *njson_var = json_value_get_string(njson_val);
#if(FEATURE_STRDUP)
    if (*njson_var)*njson_var = strdup(*njson_var);
#endif
}

#endif//_NJSON_SUPPORT_CSTR_TYPE_H_