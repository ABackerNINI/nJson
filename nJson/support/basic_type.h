#pragma once

#ifndef _NJSON_SUPPORT_BASIC_TYPE_H_
#define _NJSON_SUPPORT_BASIC_TYPE_H_

#include <cstring>
#include "support_base.h"

/*
	This file is to support the serialization and deserialization of basic types,
  	including char, bool, short, int, float, long long, double.
*/

/*! basic types should always be initialized to avoid a random value*/
/*! type 'bool' should be initialized by memset(&bool_val,-1,sizeof(bool))*/
/*! DO NOT USE TEMPLATE HERE to make sure basic types match first*/

#define NJSON_DEFAULT_VALUE_CHAR      ((char)-1)
#define NJSON_DEFAULT_VALUE_BOOL      ((short)255)
#define NJSON_DEFAULT_VALUE_SHORT     (0x6fff)
#define NJSON_DEFAULT_VALUE_INT       (0x6fffffff)
#define NJSON_DEFAULT_VALUE_FLOAT     (-1000000.125)//choose a value that float type can exactly represent
#define NJSON_DEFAULT_VALUE_LONG_LONG (0x6fffffffffffffff)
#define NJSON_DEFAULT_VALUE_DOUBLE    (-100000000000000.11)//choose a value that double type can exactly represent

template<>
struct njson_support<char> {
    static bool is_default_value(const char &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_CHAR;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const char &njson_var) {
        char tmp[2];
        {
            tmp[0] = njson_var;
            tmp[1] = '\0';
        }

        njson_value_set_value(njson_val, njson_name, json_value_init_string(tmp));
    }

    static void deserialize(JSON_Value *njson_val, char *njson_var) {
        const char *s = json_value_get_string(njson_val);
        if (s)*njson_var = s[0];
    }
};

template<>
struct njson_support<bool> {
    static bool is_default_value(const bool &njson_var) {
        const static short i = NJSON_DEFAULT_VALUE_BOOL;

        return memcmp(&njson_var, &i, sizeof(bool)) == 0;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const bool &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_boolean(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, bool *njson_var) {
        *njson_var = (json_value_get_boolean(njson_val) == 1);
    }
};

template<>
struct njson_support<short> {
    static bool is_default_value(const short &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_SHORT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const short &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, short *njson_var) {
        *njson_var = (short) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<int> {
    static bool is_default_value(const int &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_INT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const int &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, int *njson_var) {
        *njson_var = (int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<long long> {
    static bool is_default_value(const long long &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_LONG_LONG;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const long long &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, long long *njson_var) {
        *njson_var = (long long) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<float> {
    static bool is_default_value(const float &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_FLOAT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const float &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, float *njson_var) {
        *njson_var = (float) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<double> {
    static bool is_default_value(const double &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_DOUBLE;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const double &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, double *njson_var) {
        *njson_var = json_value_get_number(njson_val);
    }
};

#endif//_NJSON_SUPPORT_BASIC_TYPE_H_