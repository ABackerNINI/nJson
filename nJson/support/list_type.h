#pragma once

#ifndef _NJSON_SUPPORT_LIST_TYPE_H_
#define _NJSON_SUPPORT_LIST_TYPE_H_

#include <list>
#include "../parson/parson.h"

/*
	This file is to support the serialization and deserialization of type 'std::list<T>'.
*/

template<typename T>
inline bool njson_is_default_value(const std::list<T> &njson_var);

template<typename T>
inline JSON_Value *njson_serialize(const std::list<T> &njson_var);

template<typename T>
inline void njson_deserialize(JSON_Value *njson_val, std::list<T> *njson_var);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline bool njson_is_default_value(const std::list<T> &njson_var) {
    return njson_var.size() == 0;
}

template<typename T>
inline JSON_Value *njson_serialize(const std::list<T> &njson_var) {
    JSON_Value *doc = json_value_init_array();
    JSON_Array *arr = json_value_get_array(doc);

    typename std::list<T>::const_iterator it;
    for (it = njson_var.begin(); it != njson_var.end(); ++it) {
        json_array_append_value(arr, njson_serialize(*it));
    }

    return doc;
}

template<typename T>
inline void njson_deserialize(JSON_Value *njson_val, std::list<T> *njson_var) {
    JSON_Array *arr = json_value_get_array(njson_val);
    size_t n = json_array_get_count(arr);
    T tmp;
    for (size_t i = 0; i < n; ++i) {
        njson_deserialize(json_array_get_value(arr, i), &tmp);
        njson_var->push_back(tmp);
    }
}

#endif//_NJSON_SUPPORT_LIST_TYPE_H_