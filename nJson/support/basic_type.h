#pragma once

#ifndef _NJSON_SUPPORT_BASIC_TYPE_H_
#define _NJSON_SUPPORT_BASIC_TYPE_H_

#include <cstring>
#include <cstdlib>
#include "support_base.h"

/*
	This file is to support the serialization and deserialization of basic types,
  	including:
  	    bool,char,unsigned char,signed char,wchar_t,unsigned short,signed short,unsigned int,
  	    signed int,unsigned long,signed long,long long,unsigned long long,float,double,long double.

  	Note that type 'long double' will be converted to 'double' during (de)serialization and loss precision.
*/

/*! Basic types should always be initialized to avoid a random value*/
/*! Type 'bool' should be initialized by memset(&bool_val,-1,sizeof(bool))*/

template<>
struct njson_support<bool> {
    static bool is_default(const bool &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const bool &njson_var) {
        return json_value_init_boolean(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, bool *njson_var) {
        *njson_var = (json_value_get_boolean(njson_val) == 1);
    }
};

template<>
struct njson_support<char> {
    static bool is_default(const char &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const char &njson_var) {
        char tmp[2];
        {
            tmp[0] = njson_var;
            tmp[1] = '\0';
        }

        return json_value_init_string(tmp);
    }

    static void deserialize(JSON_Value *njson_val, char *njson_var) {
        const char *s = json_value_get_string(njson_val);
        if (s)*njson_var = s[0];
    }
};

template<>
struct njson_support<unsigned char> {
    static bool is_default(const unsigned char &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const unsigned char &njson_var) {
        char tmp[2];
        {
            tmp[0] = (char) njson_var;
            tmp[1] = '\0';
        }

        return json_value_init_string(tmp);
    }

    static void deserialize(JSON_Value *njson_val, unsigned char *njson_var) {
        const char *s = json_value_get_string(njson_val);
        if (s)*njson_var = (unsigned char) s[0];
    }
};

template<>
struct njson_support<signed char> {
    static bool is_default(const signed char &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const signed char &njson_var) {
        char tmp[2];
        {
            tmp[0] = (char) njson_var;
            tmp[1] = '\0';
        }

        return json_value_init_string(tmp);
    }

    static void deserialize(JSON_Value *njson_val, signed char *njson_var) {
        const char *s = json_value_get_string(njson_val);
        if (s)*njson_var = (signed char) s[0];
    }
};

#if(_NATIVE_WCHAR_T_DEFINED /*Windows*/ || _GLIBCXX_USE_WCHAR_T /*Unix*/)

template<>
struct njson_support<wchar_t> {
    static bool is_default(const wchar_t &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const wchar_t &njson_var) {
        char tmp[10];
        wchar_t wtmp[2];
        {
            wtmp[0] = njson_var;
            wtmp[1] = L'\0';
        }

        wcstombs(tmp, wtmp, 10);

        return json_value_init_string(tmp);
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
    static bool is_default(const unsigned short &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const unsigned short &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, unsigned short *njson_var) {
        *njson_var = (unsigned short) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<signed short> {
    static bool is_default(const short &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const signed short &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, signed short *njson_var) {
        *njson_var = (short) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<unsigned int> {
    static bool is_default(const unsigned int &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const unsigned int &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, unsigned int *njson_var) {
        *njson_var = (unsigned int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<signed int> {
    static bool is_default(const signed int &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const signed int &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, signed int *njson_var) {
        *njson_var = (int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<unsigned long> {
    static bool is_default(const unsigned long &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const unsigned long &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, unsigned long *njson_var) {
        *njson_var = (unsigned int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<signed long> {
    static bool is_default(const signed long &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const signed long &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, signed long *njson_var) {
        *njson_var = (int) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<unsigned long long> {
    static bool is_default(const unsigned long long &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const unsigned long long &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, unsigned long long *njson_var) {
        *njson_var = (unsigned long long) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<signed long long> {
    static bool is_default(const signed long long &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const signed long long &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, signed long long *njson_var) {
        *njson_var = (unsigned long long) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<float> {
    static bool is_default(const float &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const float &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, float *njson_var) {
        *njson_var = (float) json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<double> {
    static bool is_default(const double &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const double &njson_var) {
        return json_value_init_number(njson_var);
    }

    static void deserialize(JSON_Value *njson_val, double *njson_var) {
        *njson_var = json_value_get_number(njson_val);
    }
};

template<>
struct njson_support<long double> {
    static bool is_default(const long double &njson_var) {
        return false;
    }

    static JSON_Value *serialize(const long double &njson_var) {
        return json_value_init_number((double) njson_var);
    }

    static void deserialize(JSON_Value *njson_val, long double *njson_var) {
        *njson_var = (long double) json_value_get_number(njson_val);
    }
};

#endif//_NJSON_SUPPORT_BASIC_TYPE_H_