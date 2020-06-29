#pragma once

#ifndef _NJSON_SUPPORT_LIST_TYPE_H_
#define _NJSON_SUPPORT_LIST_TYPE_H_

#include <list>
#include "support_base.h"

/*
    This file is to support the serialization and deserialization of type
   'std::list<T>'.
*/

template <typename T>
struct njson_support<std::list<T> > {
    static bool is_default(const std::list<T> &njson_var) {
        return njson_var.empty();
    }

    static JSON_Value *serialize(const std::list<T> &njson_var) {
        JSON_Value *doc = json_value_init_array();
        JSON_Array *arr = json_value_get_array(doc);

        typename std::list<T>::const_iterator it;
        for (it = njson_var.begin(); it != njson_var.end(); ++it) {
            json_array_append_value(arr, njson_support_serialize(*it));
        }

        return doc;
    }

    static void deserialize(JSON_Value *njson_val, std::list<T> *njson_var) {
        JSON_Array *arr = json_value_get_array(njson_val);
        size_t n = json_array_get_count(arr);
        T tmp;
        for (size_t i = 0; i < n; ++i) {
            njson_support_deserialize(json_array_get_value(arr, i), &tmp);
            njson_var->push_back(tmp);
        }
    }
};

#endif  //_NJSON_SUPPORT_LIST_TYPE_H_
