#pragma once

#ifndef _NJSON_SUPPORT_SUPPORT_BASE_H_
#define _NJSON_SUPPORT_SUPPORT_BASE_H_

#include "../type_traits/type_traits.h"
#include "../parson/parson.h"

//#define NJSON_FEATURE_JSON_VALUE_SET_VALUE_FUNCS  0
//
//#if(NJSON_FEATURE_JSON_VALUE_SET_VALUE_FUNCS)
//
//static void njson_value_set_value_object(JSON_Value *njson_val_val, const char *njson_name, JSON_Value *njson_val_var) {
//    json_object_set_value(json_value_get_object(njson_val_val), njson_name, njson_val_var);
//}
//
//static void njson_value_set_value_array(JSON_Value *njson_val_val, const char *njson_name, JSON_Value *njson_val_var) {
//    json_array_append_value(json_value_get_array(njson_val_val), njson_val_var);
//}
//
//#endif
//
//inline void njson_value_set_value(JSON_Value *njson_val_val, const char *njson_name, JSON_Value *njson_val_var) {
//#if(NJSON_FEATURE_JSON_VALUE_SET_VALUE_FUNCS)
//    typedef void (*json_value_set_value_func)(JSON_Value *, const char *, JSON_Value *);
//
//    static json_value_set_value_func json_value_set_value_funcs[] = {
//            NULL, NULL, NULL, NULL, njson_value_set_value_object, njson_value_set_value_array
//    };
//
//    json_value_set_value_funcs[json_value_get_type(njson_val_val)](njson_val_val, njson_name, njson_val_var);
//#else
//    switch (json_value_get_type(njson_val_val)) {
//        case JSONObject:
//            json_object_set_value(json_value_get_object(njson_val_val), njson_name, njson_val_var);
//            break;
//        case JSONArray:
//            json_array_append_value(json_value_get_array(njson_val_val), njson_val_var);
//            break;
//        default:
//            break;
//    }
//#endif
//}

template<typename T>
struct njson_support {
    static bool is_default(const T &njson_var) {
        return njson_var.njson_is_default();
    }

    static JSON_Value *serialize(const T &njson_var) {
        return njson_var.njson_serialize();
    }

    static void deserialize(JSON_Value *njson_val, T *njson_var) {
        njson_var->njson_deserialize(njson_val);
    }
};

template<typename T>
bool njson_support_is_default(const T &val) {
    return njson_support<typename std::remove_cv<T>::type>::is_default(val);
}

template<typename T>
JSON_Value *njson_support_serialize(const T &val) {
    return njson_support<typename std::remove_cv<T>::type>::serialize(val);
}

template<typename T>
void njson_support_deserialize(JSON_Value *njson_val, T *njson_var) {
    return njson_support<typename std::remove_cv<T>::type>::deserialize(njson_val, njson_var);
}

#endif //_NJSON_SUPPORT_SUPPORT_BASE_H_
