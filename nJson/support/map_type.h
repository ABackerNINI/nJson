#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_MAP_TYPE_H_
#define _UTILITIES_JSON_SUPPORT_MAP_TYPE_H_

#include <map>
#include "../parson.h"
#include "to_string.h"
#include "string_to.h"
#include "string_type.h"

/*
	This file is to support the serialization and deserialization of type 'std::map<_T1,_T2>'.
	note that this file relies on "to_string.h" and "string_to.h".
*/

template<typename _T_KEY, typename _T_VAL>
inline bool is_default_value(const std::map<_T_KEY, _T_VAL> &val) {
    return val.size() == 0;
}

/*njson_set_value*/
template<typename _T_KEY, typename _T_VAL>
void njson_set_value(JSON_Object *obj, const char *key, const std::map<_T_KEY, _T_VAL> &val) {
    if (key != NULL) {
        json_object_set_value(obj, key, json_value_init_object());
        JSON_Value *doc = json_object_get_value(obj, key);
        obj = json_value_get_object(doc);
    }
    typename std::map<_T_KEY, _T_VAL>::const_iterator it;
    for (it = val.begin(); it != val.end(); ++it) {
        njson_set_value(obj, to_string(it->first).c_str(), it->second);
    }
}

template<typename _T_KEY, typename _T_VAL>
void njson_set_value(JSON_Array *arr, const std::map<_T_KEY, _T_VAL> &val) {
    JSON_Value *doc = json_value_init_object();
    JSON_Object *obj = json_value_get_object(doc);
    njson_set_value(obj, NULL, val);
    json_array_append_value(arr, doc);
}

/*njson_get_value*/
template<typename _T_KEY, typename _T_VAL>
void njson_get_value(JSON_Object *obj, const char *key, std::map<_T_KEY, _T_VAL> *val) {
    if (key != NULL)obj = json_object_get_object(obj, key);
    if (obj == NULL)return;
    size_t n = json_object_get_count(obj);
    const char *name;
    _T_KEY mkey;
    _T_VAL mval;
    for (size_t i = 0; i < n; ++i) {
        name = json_object_get_name(obj, i);
        string_to(name, &mkey);
        njson_get_value(obj, name, &mval);
        (*val)[mkey] = mval;
    }
}

template<typename _T_KEY, typename _T_VAL>
void njson_get_value(JSON_Array *arr, size_t index, std::map<_T_KEY, _T_VAL> *val) {
    size_t n = json_array_get_count(arr);
    JSON_Object *obj = json_array_get_object(arr, index);
    njson_get_value(obj, NULL, val);
}

#endif//_UTILITIES_JSON_SUPPORT_MAP_TYPE_H_