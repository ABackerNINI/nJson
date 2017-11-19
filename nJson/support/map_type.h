#pragma once

#ifndef _NJSON_SUPPORT_MAP_TYPE_H_
#define _NJSON_SUPPORT_MAP_TYPE_H_

#include "support_base.h"

#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "../type_traits/type_traits.h"

/*
	This file is to support the serialization and deserialization of type 'std::map<T1,T2>'.
	Need to implement:
        template<>struct njson_map_support<T>::static std::string to_string(const bool &val);
        template<>struct njson_map_support<T>::static void string_to(const char *s, bool *val);
*/

template<typename T>
struct njson_map_support {
};

template<>
struct njson_map_support<bool> {
    static std::string to_string(const bool &val) {
        return val ? std::string("true") : std::string("false");
    }

    static void string_to(const char *s, bool *val) {
        *val = (strcmp(s, "true") == 0);
    }
};

template<>
struct njson_map_support<char> {
    static std::string to_string(const char &val) {
        char tmp[2];
        tmp[0] = val;
        tmp[1] = '\0';

        return std::string(tmp);
    }

    static void string_to(const char *s, char *val) {
        *val = s[0];
    }
};

template<>
struct njson_map_support<unsigned char> {
    static std::string to_string(const unsigned char &val) {
        char tmp[2];
        tmp[0] = (char) val;
        tmp[1] = '\0';

        return std::string(tmp);
    }

    static void string_to(const char *s, unsigned char *val) {
        *val = (unsigned char) s[0];
    }
};

template<>
struct njson_map_support<signed char> {
    static std::string to_string(const signed char &val) {
        char tmp[2];
        tmp[0] = (char) val;
        tmp[1] = '\0';

        return std::string(tmp);
    }

    static void string_to(const char *s, signed char *val) {
        *val = (signed char) s[0];
    }
};

#if(_NATIVE_WCHAR_T_DEFINED /*Windows*/ || _GLIBCXX_USE_WCHAR_T /*Unix*/)

template<>
struct njson_map_support<wchar_t> {
    static std::string to_string(const wchar_t &val) {
        char tmp[10];
        wchar_t wtmp[2];
        {
            wtmp[0] = val;
            wtmp[1] = L'\0';
        }

        wcstombs(tmp, wtmp, 10);

        return std::string(tmp);
    }

    static void string_to(const char *s, wchar_t *val) {
        wchar_t wtmp[2];

        mbstowcs(wtmp, s, 2);

        *val = wtmp[0];
    }
};

#endif

template<typename T>
struct njson_map_support_integral_unsigned_base {
    static std::string to_string(const T &val) {
        char tmp[30];
        sprintf(tmp, "%llu", (unsigned long long) val);

        return std::string(tmp);
    }

    static void string_to(const char *s, T *val) {
        *val = (T) strtoull(s, NULL, 10);
    }
};

template<typename T>
struct njson_map_support_integral_signed_base {
    static std::string to_string(const T &val) {
        char tmp[30];
        sprintf(tmp, "%lld", (signed long long) val);

        return std::string(tmp);
    }

    static void string_to(const char *s, T *val) {
        *val = (T) strtoll(s, NULL, 10);
    }
};

template<>
struct njson_map_support<unsigned short> : njson_map_support_integral_unsigned_base<unsigned short> {
};

template<>
struct njson_map_support<signed short> : njson_map_support_integral_signed_base<signed short> {
};

template<>
struct njson_map_support<unsigned int> : njson_map_support_integral_unsigned_base<signed short> {
};

template<>
struct njson_map_support<signed int> : njson_map_support_integral_signed_base<signed int> {
};

template<>
struct njson_map_support<unsigned long> : njson_map_support_integral_unsigned_base<unsigned long> {
};

template<>
struct njson_map_support<signed long> : njson_map_support_integral_signed_base<signed long> {
};

template<>
struct njson_map_support<unsigned long long> : njson_map_support_integral_unsigned_base<unsigned long long> {
};

template<>
struct njson_map_support<signed long long> : njson_map_support_integral_signed_base<signed long long> {
};

template<typename T>
struct njson_map_support_floating_point_base {
    static std::string to_string(const T &val) {
        char tmp[30];
        sprintf(tmp, "%lf", (double) val);

        return std::string(tmp);
    }

    static void string_to(const char *s, T *val) {
        *val = (T) strtod(s, NULL);
    }
};

template<>
struct njson_map_support<float> : njson_map_support_floating_point_base<float> {
};

template<>
struct njson_map_support<double> : njson_map_support_floating_point_base<double> {
};

template<>
struct njson_map_support<long double> : njson_map_support_floating_point_base<long double> {
};

template<typename T>
std::string njson_to_string(const T &val) {
    return njson_map_support<typename std::remove_cv<T>::type>::to_string(val);
}

template<typename T>
void njson_string_to(const char *s, T *val) {
    njson_map_support<typename std::remove_cv<T>::type>::string_to(s, val);
}

template<>
struct njson_map_support<std::string> {
    static std::string to_string(const std::string &val) {
        return val;
    }

    static void string_to(const char *s, std::string *val) {
        *val = std::string(s);
    }
};

template<>
struct njson_map_support<char *> {
    static std::string to_string(const char *val) {
        return std::string(val);
    }

    static void string_to(const char *s, char **val) {
        *val = strdup(s);
    }
};

template<>
struct njson_map_support<const char *> {
    static std::string to_string(const char *val) {
        return std::string(val);
    }

    static void string_to(const char *s, const char **val) {
        ////TODO:test
        *val = s;
    }
};

/*support std::map<T1, T2>*/
template<typename T1, typename T2>
struct njson_support<std::map<T1, T2> > {
    static bool is_default(const std::map<T1, T2> &njson_var) {
        return njson_var.empty();
    }

    static JSON_Value *serialize(const std::map<T1, T2> &njson_var) {
        JSON_Value *doc = json_value_init_object();
        JSON_Object *obj = json_value_get_object(doc);

        typename std::map<T1, T2>::const_iterator it;
        for (it = njson_var.begin(); it != njson_var.end(); ++it) {
            json_object_set_value(obj, njson_to_string(it->first).c_str(), njson_support_serialize(it->second));
        }

        return doc;
    }

    static void deserialize(JSON_Value *njson_val, std::map<T1, T2> *njson_var) {
        JSON_Object *obj = json_value_get_object(njson_val);
        size_t n = json_object_get_count(obj);
        const char *name;
        T1 key;
        T2 val;
        for (size_t i = 0; i < n; ++i) {
            name = json_object_get_name(obj, i);
            njson_string_to(name, &key);
            njson_support_deserialize(json_object_get_value_at(obj, i), &val);
            (*njson_var)[key] = val;
        }
    }
};

#endif//_NJSON_SUPPORT_MAP_TYPE_H_