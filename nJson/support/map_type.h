#pragma once

#ifndef _NJSON_SUPPORT_MAP_TYPE_H_
#define _NJSON_SUPPORT_MAP_TYPE_H_

#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "../parson/parson.h"

/*
	This file is to support the serialization and deserialization of type 'std::map<T1,T2>'.
	Need to implement njson_to_string(T1) and njson_string_to(const char *,T1*).
*/

/*njson_to_string*/
inline std::string njson_to_string(const char &val);

inline std::string njson_to_string(const bool &val);

inline std::string njson_to_string(const char *&val);

inline std::string njson_to_string(const double &val);

inline const std::string &njson_to_string(const std::string &val);

/*njson_string_to*/
inline void njson_string_to(const char *s, char *val);

inline void njson_string_to(const char *s, bool *val);

inline void njson_string_to(const char *s, double *val);

inline void njson_string_to(const char *s, const char **val);

inline void njson_string_to(const char *s, std::string *val);

/*support map<T1,T2>*/
template<typename T1, typename T2>
inline bool njson_is_default_value(const std::map<T1, T2> &njson_var);

template<typename T1, typename T2>
inline JSON_Value *njson_serialize(const std::map<T1, T2> &njson_var);

template<typename T1, typename T2>
inline void njson_deserialize(JSON_Value *njson_val, std::map<T1, T2> *njson_var);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline std::string njson_to_string(const char &val) {
    char tmp[2];
    tmp[0] = val;
    tmp[1] = '\0';

    return std::string(tmp);
}

inline std::string njson_to_string(const bool &val) {
    return val ? std::string("true") : std::string("false");
}

inline std::string njson_to_string(const char *&val) {
    return std::string(val);
}

inline std::string njson_to_string(const double &val) {
    char tmp[30];
    sprintf(tmp, "%lf", val);
    return std::string(tmp);
}

inline const std::string &njson_to_string(const std::string &val) {
    return val;
}

/*string_to*/
inline void njson_string_to(const char *s, char *val) {
    *val = s[0];
}

inline void njson_string_to(const char *s, bool *val) {
    *val = (strcmp(s, "true") == 0);
}

inline void njson_string_to(const char *s, double *val) {
    *val = atof(s);
}

inline void njson_string_to(const char *s, const char **val) {
    *val = s;
}

inline void njson_string_to(const char *s, std::string *val) {
    *val = std::string(s);
}

template<typename T1, typename T2>
inline bool njson_is_default_value(const std::map<T1, T2> &njson_var) {
    return njson_var.size() == 0;
}

template<typename T1, typename T2>
inline JSON_Value *njson_serialize(const std::map<T1, T2> &njson_var) {
    JSON_Value *doc = json_value_init_object();
    JSON_Object *obj = json_value_get_object(doc);

    typename std::map<T1, T2>::const_iterator it;
    for (it = njson_var.begin(); it != njson_var.end(); ++it) {
        json_object_set_value(obj, njson_to_string(it->first).c_str(), njson_serialize(it->second));
    }

    return doc;
};

template<typename T1, typename T2>
inline void njson_deserialize(JSON_Value *njson_val, std::map<T1, T2> *njson_var) {
    JSON_Object *obj = json_value_get_object(njson_val);
    size_t n = json_object_get_count(obj);
    const char *name;
    T1 key;
    T2 val;
    for (size_t i = 0; i < n; ++i) {
        name = json_object_get_name(obj, i);
        njson_string_to(name, &key);
        njson_deserialize(json_object_get_value_at(obj, i), &val);
        (*njson_var)[key] = val;
    }
};

#endif//_NJSON_SUPPORT_MAP_TYPE_H_