#pragma once

#ifndef _NJSON_NJSON_H_
#define _NJSON_NJSON_H_

#define _NJSON_IS_DEFAULT_FUNC  ::njson_support_is_default
#define _NJSON_SERIALIZE_FUNC   ::njson_support_serialize
#define _NJSON_DESERIALIZE_FUNC ::njson_support_deserialize

#define _NJSON_SERIALIZE_INIT(ROOT)   JSON_Value *ROOT = json_value_init_object()
#define _NJSON_DESERIALIZE_INIT(TEMP) JSON_Value *TEMP = NULL

#define _NJSON_SET_IF_NOT_DEFAULT(ROOT, K, M) \
    if(!_NJSON_IS_DEFAULT_FUNC(M)) \
        json_object_set_value(json_value_get_object(ROOT),K,_NJSON_SERIALIZE_FUNC(M))

#define _NJSON_SET(ROOT, K, M) _NJSON_SET_IF_NOT_DEFAULT(ROOT,K,M)

#define _NJSON_GET(ROOT, K, M, T) \
    T = json_object_get_value(json_value_get_object(ROOT),K); \
    if(T) \
        _NJSON_DESERIALIZE_FUNC(T,M)

#define _NJSON_SERIALIZE_SUPER_CLASS(SUPER, ROOT) njson_value_move(_NJSON_SERIALIZE_FUNC(*(SUPER)),ROOT)
#define _NJSON_DESERIALIZE_SUPER_CLASS(SUPER, ROOT) _NJSON_DESERIALIZE_FUNC(ROOT,SUPER)

#include "parson/parson.h"

#include "support/support_base.h"
#include "support/basic_type.h"
#include "support/cstr_type.h"
#include "support/string_type.h"

#include "support/list_type.h"
#include "support/vector_type.h"
#include "support/map_type.h"
#include "support/pointer_type.h"

inline size_t njson_value_move(JSON_Value *src_njson_val, JSON_Value *des_njson_val) {
    if (src_njson_val == NULL || des_njson_val == NULL) {
        return 0;
    }

    if (src_njson_val->type != JSONObject || des_njson_val->type != JSONObject) {
        return 0;
    }
    JSON_Object *src_obj = src_njson_val->value.object;
    JSON_Object *des_obj = des_njson_val->value.object;

    for (size_t i = 0; i < src_obj->count; ++i) {
        src_obj->values[i]->parent = NULL;
        json_object_set_value(des_obj, src_obj->names[i], src_obj->values[i]);
    }

    return src_obj->count;
}

#endif//_NJSON_NJSON_H_