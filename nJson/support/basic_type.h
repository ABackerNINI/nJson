#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_BASIC_TYPE_H_
#define _UTILITIES_JSON_SUPPORT_BASIC_TYPE_H_

#include <string>
#include <string.h>
#include "../parson.h"

/*
	This file is to support the serialization and deserialization of basic types,
  	including char, bool, short, int, float, long long, double.
*/

/*! basic types should always be initialized to avoid a random value*/
/*! type 'bool' should be initialized by memset(&bool_val,-1,sizeof(bool))*/
/*! DO NOT USE TEMPLATE HEARE to make sure basic types match first*/

#define DEFAULT_VALUE_CHAR            (char)-1
#define DEFAULT_VALUE_BOOL            (short)255
#define DEFAULT_VALUE_SHORT            0x6fff
#define DEFAULT_VALUE_INT            0x6fffffff
#define DEFAULT_VALUE_FLOAT            -1000000.125            //choose a value that float type can exactly represent
#define DEFAULT_VALUE_LONG_LONG        0x6fffffffffffffff
#define DEFAULT_VALUE_DOUBLE        -100000000000000.11        //choose a value that double type can exactly represent

/*
 * Declarations:
 * */

/*is_default_value*/
inline bool is_default_value(const char &val);

inline bool is_default_value(const bool &val);

inline bool is_default_value(const short &val);

inline bool is_default_value(const int &val);

inline bool is_default_value(const float &val);

inline bool is_default_value(const long long &val);

inline bool is_default_value(const double &val);

/*njson_set_value*/
inline void njson_set_value(JSON_Object *obj, const char *key, const char &val);

inline void njson_set_value(JSON_Object *obj, const char *key, const bool &val);

inline void njson_set_value(JSON_Object *obj, const char *key, const short &val);

inline void njson_set_value(JSON_Object *obj, const char *key, const int &val);

inline void njson_set_value(JSON_Object *obj, const char *key, const float &val);

inline void njson_set_value(JSON_Object *obj, const char *key, const long long &val);

inline void njson_set_value(JSON_Object *obj, const char *key, const double &val);

inline void njson_set_value(JSON_Array *arr, const char &val);

inline void njson_set_value(JSON_Array *arr, const bool &val);

inline void njson_set_value(JSON_Array *arr, const short &val);

inline void njson_set_value(JSON_Array *arr, const int &val);

inline void njson_set_value(JSON_Array *arr, const float &val);

inline void njson_set_value(JSON_Array *arr, const long long &val);

inline void njson_set_value(JSON_Array *arr, const double &val);

/*njson_get_value*/
inline void njson_get_value(JSON_Object *obj, const char *key, char *val);

inline void njson_get_value(JSON_Object *obj, const char *key, bool *val);

inline void njson_get_value(JSON_Object *obj, const char *key, short *val);

inline void njson_get_value(JSON_Object *obj, const char *key, int *val);

inline void njson_get_value(JSON_Object *obj, const char *key, float *val);

inline void njson_get_value(JSON_Object *obj, const char *key, long long *val);

inline void njson_get_value(JSON_Object *obj, const char *key, double *val);

inline void njson_get_value(JSON_Array *arr, size_t index, char *val);

inline void njson_get_value(JSON_Array *arr, size_t index, bool *val);

inline void njson_get_value(JSON_Array *arr, size_t index, short *val);

inline void njson_get_value(JSON_Array *arr, size_t index, int *val);

inline void njson_get_value(JSON_Array *arr, size_t index, float *val);

inline void njson_get_value(JSON_Array *arr, size_t index, long long *val);

inline void njson_get_value(JSON_Array *arr, size_t index, double *val);

/*
 * Definitions:
 * */

/*is_default_value*/
inline bool is_default_value(const char &val) {
    return val == DEFAULT_VALUE_CHAR;
}

inline bool is_default_value(const bool &val) {
    const static short i = 255;
    return memcmp(&val, &i, sizeof(bool)) == 0;
}

inline bool is_default_value(const short &val) {
    return val == DEFAULT_VALUE_SHORT;
}

inline bool is_default_value(const int &val) {
    return val == DEFAULT_VALUE_INT;
}

inline bool is_default_value(const float &val) {
    return val == DEFAULT_VALUE_FLOAT;
}

inline bool is_default_value(const long long &val) {
    return val == DEFAULT_VALUE_LONG_LONG;
}

inline bool is_default_value(const double &val) {
    return val == DEFAULT_VALUE_DOUBLE;
}

/*njson_set_value*/
inline void njson_set_value(JSON_Object *obj, const char *key, const char &val) {
    json_object_set(obj, key, val);
}

inline void njson_set_value(JSON_Object *obj, const char *key, const bool &val) {
    json_object_set(obj, key, val);
}

inline void njson_set_value(JSON_Object *obj, const char *key, const short &val) {
    json_object_set(obj, key, val);
}

inline void njson_set_value(JSON_Object *obj, const char *key, const int &val) {
    json_object_set(obj, key, val);
}

inline void njson_set_value(JSON_Object *obj, const char *key, const float &val) {
    json_object_set(obj, key, val);
}

inline void njson_set_value(JSON_Object *obj, const char *key, const long long &val) {
    json_object_set(obj, key, val);
}

inline void njson_set_value(JSON_Object *obj, const char *key, const double &val) {
    json_object_set(obj, key, val);
}

inline void njson_set_value(JSON_Array *arr, const char &val) {
    json_array_append(arr, val);
}

inline void njson_set_value(JSON_Array *arr, const bool &val) {
    json_array_append(arr, val);
}

inline void njson_set_value(JSON_Array *arr, const short &val) {
    json_array_append(arr, val);
}

inline void njson_set_value(JSON_Array *arr, const int &val) {
    json_array_append(arr, val);
}

inline void njson_set_value(JSON_Array *arr, const float &val) {
    json_array_append(arr, val);
}

inline void njson_set_value(JSON_Array *arr, const long long &val) {
    json_array_append(arr, val);
}

inline void njson_set_value(JSON_Array *arr, const double &val) {
    json_array_append(arr, val);
}

/*njson_get_value*/
inline void njson_get_value(JSON_Object *obj, const char *key, char *val) {
    if (json_object_has_value(obj, key))
        *val = json_object_get<char>(obj, key);
}

inline void njson_get_value(JSON_Object *obj, const char *key, bool *val) {
    if (json_object_has_value(obj, key))
        *val = json_object_get<bool>(obj, key);
}

inline void njson_get_value(JSON_Object *obj, const char *key, short *val) {
    if (json_object_has_value(obj, key))
        *val = json_object_get<short>(obj, key);
}

inline void njson_get_value(JSON_Object *obj, const char *key, int *val) {
    if (json_object_has_value(obj, key))
        *val = json_object_get<int>(obj, key);
}

inline void njson_get_value(JSON_Object *obj, const char *key, float *val) {
    if (json_object_has_value(obj, key))
        *val = json_object_get<float>(obj, key);
}

inline void njson_get_value(JSON_Object *obj, const char *key, long long *val) {
    if (json_object_has_value(obj, key))
        *val = json_object_get<long long>(obj, key);
}

inline void njson_get_value(JSON_Object *obj, const char *key, double *val) {
    if (json_object_has_value(obj, key))
        *val = json_object_get<double>(obj, key);
}

inline void njson_get_value(JSON_Array *arr, size_t index, char *val) {
    *val = json_array_get<char>(arr, index);
}

inline void njson_get_value(JSON_Array *arr, size_t index, bool *val) {
    *val = json_array_get<bool>(arr, index);
}

inline void njson_get_value(JSON_Array *arr, size_t index, short *val) {
    *val = json_array_get<short>(arr, index);
}

inline void njson_get_value(JSON_Array *arr, size_t index, int *val) {
    *val = json_array_get<int>(arr, index);
}

inline void njson_get_value(JSON_Array *arr, size_t index, float *val) {
    *val = json_array_get<float>(arr, index);
}

inline void njson_get_value(JSON_Array *arr, size_t index, long long *val) {
    *val = json_array_get<long long>(arr, index);
}

inline void njson_get_value(JSON_Array *arr, size_t index, double *val) {
    *val = json_array_get<double>(arr, index);
}

#endif//_UTILITIES_JSON_SUPPORT_BASIC_TYPE_H_