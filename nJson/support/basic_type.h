#pragma once

#ifndef _NJSON_SUPPORT_BASIC_TYPE_H_
#define _NJSON_SUPPORT_BASIC_TYPE_H_

#include <cstring>
#include <cstdlib>
#include "support_base.h"

/*
	This file is to support the serialization and deserialization of basic types,
  	including char, bool, short, int, float, long long, double.
*/

/*! basic types should always be initialized to avoid a random value*/
/*! type 'bool' should be initialized by memset(&bool_val,-1,sizeof(bool))*/
/*! DO NOT USE TEMPLATE HERE to make sure basic types match first*/

#define NJSON_DEFAULT_VALUE_BOOL      ((short)-1)
#define NJSON_DEFAULT_VALUE_CHAR      ((char)-1)
#define NJSON_DEFAULT_VALUE_SHORT     (0x6fff)
#define NJSON_DEFAULT_VALUE_INT       (0x6fffffff)
#define NJSON_DEFAULT_VALUE_FLOAT     (-1000000.125)//choose a value that float type can exactly represent
#define NJSON_DEFAULT_VALUE_LONG_LONG (0x6fffffffffffffff)
#define NJSON_DEFAULT_VALUE_DOUBLE    (-100000000000000.11)//choose a value that double type can exactly represent

template<>
struct njson_support<bool> {
    static bool is_default_value(const bool &njson_var) {
        const static signed short i = NJSON_DEFAULT_VALUE_BOOL;

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
struct njson_support<unsigned char> {
    static bool is_default_value(const unsigned char &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_CHAR;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const unsigned char &njson_var) {
        char tmp[2];
        {
            tmp[0] = (char) njson_var;
            tmp[1] = '\0';
        }

        njson_value_set_value(njson_val, njson_name, json_value_init_string(tmp));
    }

    static void deserialize(JSON_Value *njson_val, unsigned char *njson_var) {
        const char *s = json_value_get_string(njson_val);
        if (s)*njson_var = (unsigned char) s[0];
    }
};

template<>
struct njson_support<signed char> {
    static bool is_default_value(const signed char &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_CHAR;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const signed char &njson_var) {
        char tmp[2];
        {
            tmp[0] = (char) njson_var;
            tmp[1] = '\0';
        }

        njson_value_set_value(njson_val, njson_name, json_value_init_string(tmp));
    }

    static void deserialize(JSON_Value *njson_val, signed char *njson_var) {
        const char *s = json_value_get_string(njson_val);
        if (s)*njson_var = (signed char) s[0];
    }
};

#if(_NATIVE_WCHAR_T_DEFINED /*Windows*/ || _GLIBCXX_USE_WCHAR_T /*Unix*/)

template<>
struct njson_support<wchar_t> {
    static bool is_default_value(const wchar_t &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_CHAR;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const wchar_t &njson_var) {
        char tmp[10];
        wchar_t wtmp[2];
        {
            wtmp[0] = njson_var;
            wtmp[1] = L'\0';
        }

        wcstombs(tmp, wtmp, 10);

        njson_value_set_value(njson_val, njson_name, json_value_init_string(tmp));
    }

    static void deserialize(JSON_Value *njson_val, wchar_t *njson_var) {
        const char *s = json_value_get_string(njson_val);

        if (s) {
            wchar_t tmp[2];

            mbstowcs(tmp, s, 2);

            *njson_var = tmp[0];
        }
    }
};

#endif

template<>
struct njson_support<unsigned short> {
    static bool is_default_value(const unsigned short &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_SHORT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const unsigned short &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, unsigned short *njson_var) {
        *njson_var = (unsigned short) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<signed short> {
    static bool is_default_value(const short &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_SHORT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const signed short &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, signed short *njson_var) {
        *njson_var = (short) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<unsigned int> {
    static bool is_default_value(const unsigned int &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_INT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const unsigned int &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, unsigned int *njson_var) {
        *njson_var = (unsigned int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<signed int> {
    static bool is_default_value(const signed int &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_INT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const signed int &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, signed int *njson_var) {
        *njson_var = (int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<unsigned long> {
    static bool is_default_value(const unsigned long &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_INT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const unsigned long &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, unsigned long *njson_var) {
        *njson_var = (unsigned int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<signed long> {
    static bool is_default_value(const signed long &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_INT;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const signed long &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, signed long *njson_var) {
        *njson_var = (int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<unsigned long long> {
    static bool is_default_value(const unsigned long long &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_LONG_LONG;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const unsigned long long &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, unsigned long long *njson_var) {
        *njson_var = (unsigned long long) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<signed long long> {
    static bool is_default_value(const signed long long &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_LONG_LONG;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const signed long long &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number(njson_var));
    }

    static void deserialize(JSON_Value *njson_val, signed long long *njson_var) {
        *njson_var = (unsigned long long) json_value_get_number(njson_val);
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

template<>
struct njson_support<long double> {
    static bool is_default_value(const long double &njson_var) {
        return njson_var == NJSON_DEFAULT_VALUE_DOUBLE;
    }

    static void serialize(JSON_Value *njson_val, const char *njson_name, const long double &njson_var) {
        njson_value_set_value(njson_val, njson_name, json_value_init_number((double) njson_var));
    }

    static void deserialize(JSON_Value *njson_val, long double *njson_var) {
        *njson_var = (long double) json_value_get_number(njson_val);
    }
};

#endif//_NJSON_SUPPORT_BASIC_TYPE_H_