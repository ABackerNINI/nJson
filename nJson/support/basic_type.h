#pragma once

#ifndef _NJSON_SUPPORT_BASIC_TYPE_H_
#define _NJSON_SUPPORT_BASIC_TYPE_H_

#include <cstring>
#include "../parson/parson.h"

/*
	This file is to support the serialization and deserialization of basic types,
  	including char, bool, short, int, float, long long, double.
*/

/*! basic types should always be initialized to avoid a random value*/
/*! type 'bool' should be initialized by memset(&bool_val,-1,sizeof(bool))*/
/*! DO NOT USE TEMPLATE HEARE to make sure basic types match first*/

#define DEFAULT_VALUE_CHAR      ((char)-1)
#define DEFAULT_VALUE_BOOL      ((short)255)
#define DEFAULT_VALUE_SHORT     (0x6fff)
#define DEFAULT_VALUE_INT       (0x6fffffff)
#define DEFAULT_VALUE_FLOAT     (-1000000.125)//choose a value that float type can exactly represent
#define DEFAULT_VALUE_LONG_LONG (0x6fffffffffffffff)
#define DEFAULT_VALUE_DOUBLE    (-100000000000000.11)//choose a value that double type can exactly represent

/*is_default_value*/
inline bool njson_is_default_value(const char &njson_var);

inline bool njson_is_default_value(const bool &njson_var);

inline bool njson_is_default_value(const short &njson_var);

inline bool njson_is_default_value(const int &njson_var);

inline bool njson_is_default_value(const float &njson_var);

inline bool njson_is_default_value(const long long &njson_var);

inline bool njson_is_default_value(const double &njson_var);

/*njson_serialize*/
inline JSON_Value *njson_serialize(const char &njson_var);

inline JSON_Value *njson_serialize(const bool &njson_var);

inline JSON_Value *njson_serialize(const short &njson_var);

inline JSON_Value *njson_serialize(const int &njson_var);

inline JSON_Value *njson_serialize(const float &njson_var);

inline JSON_Value *njson_serialize(const long long &njson_var);

inline JSON_Value *njson_serialize(const double &njson_var);

/*njson_deserialize*/
inline void njson_deserialize(JSON_Value *njson_val, char *njson_var);

inline void njson_deserialize(JSON_Value *njson_val, bool *njson_var);

inline void njson_deserialize(JSON_Value *njson_val, short *njson_var);

inline void njson_deserialize(JSON_Value *njson_val, int *njson_var);

inline void njson_deserialize(JSON_Value *njson_val, float *njson_var);

inline void njson_deserialize(JSON_Value *njson_val, long long *njson_var);

inline void njson_deserialize(JSON_Value *njson_val, double *njson_var);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*is_default_value*/
inline bool njson_is_default_value(const char &njson_var) {
    return njson_var == DEFAULT_VALUE_CHAR;
}

inline bool njson_is_default_value(const bool &njson_var) {
    const static short i = 255;
    return memcmp(&njson_var, &i, sizeof(bool)) == 0;
}

inline bool njson_is_default_value(const short &njson_var) {
    return njson_var == DEFAULT_VALUE_SHORT;
}

inline bool njson_is_default_value(const int &njson_var) {
    return njson_var == DEFAULT_VALUE_INT;
}

inline bool njson_is_default_value(const float &njson_var) {
    return njson_var == DEFAULT_VALUE_FLOAT;
}

inline bool njson_is_default_value(const long long &njson_var) {
    return njson_var == DEFAULT_VALUE_LONG_LONG;
}

inline bool njson_is_default_value(const double &njson_var) {
    return njson_var == DEFAULT_VALUE_DOUBLE;
}

/*njson_serialize*/
inline JSON_Value *njson_serialize(const char &njson_var) {
    char tmp[2];
    tmp[0] = njson_var;
    tmp[1] = '\0';

    return json_value_init_string(tmp);
}

inline JSON_Value *njson_serialize(const bool &njson_var) {
    return json_value_init_boolean(njson_var);
}

inline JSON_Value *njson_serialize(const short &njson_var) {
    return json_value_init_number(njson_var);
}

inline JSON_Value *njson_serialize(const int &njson_var) {
    return json_value_init_number(njson_var);
}

inline JSON_Value *njson_serialize(const float &njson_var) {
    return json_value_init_number(njson_var);
}

inline JSON_Value *njson_serialize(const long long &njson_var) {
    return json_value_init_number(njson_var);
}

inline JSON_Value *njson_serialize(const double &njson_var) {
    return json_value_init_number(njson_var);
}

/*njson_deserialize*/
inline void njson_deserialize(JSON_Value *njson_val, char *njson_var) {
    const char *s = json_value_get_string(njson_val);
    if (s)*njson_var = s[0];
}

inline void njson_deserialize(JSON_Value *njson_val, bool *njson_var) {
    *njson_var = (json_value_get_boolean(njson_val) == 1);
}

inline void njson_deserialize(JSON_Value *njson_val, short *njson_var) {
    *njson_var = (short) json_value_get_number(njson_val);
}

inline void njson_deserialize(JSON_Value *njson_val, int *njson_var) {
    *njson_var = (int) json_value_get_number(njson_val);
}

inline void njson_deserialize(JSON_Value *njson_val, float *njson_var) {
    *njson_var = (float) json_value_get_number(njson_val);
}

inline void njson_deserialize(JSON_Value *njson_val, long long *njson_var) {
    *njson_var = (long long) json_value_get_number(njson_val);
}

inline void njson_deserialize(JSON_Value *njson_val, double *njson_var) {
    *njson_var = json_value_get_number(njson_val);
}

#endif//_NJSON_SUPPORT_BASIC_TYPE_H_