#pragma once

#ifndef _NJSON_DEF_H_
#define _NJSON_DEF_H_

#include "nJson.h"

#define NJSON_SERIALIZE_INIT _NJSON_SERIALIZE_INIT(njson_val)
#define NJSON_DESERIALIZE_INIT _NJSON_DESERIALIZE_INIT(_njson_tmp_val_)

#define NJSON_SET(M) _NJSON_SET(njson_val,#M,M)
#define NJSON_SET_AS_TYPE(M, T) _NJSON_SET(njson_val,#M,(T)(M))
#define NJSON_GET(M) _NJSON_GET(njson_val,#M,&(M),_njson_tmp_val_)
#define NJSON_GET_AS_TYPE(M, T) _NJSON_GET(njson_val,#M,(T *)(&(M)))

#define NJSON_SET_IF_KEY(M) if(strcmp(#M,_key_) == 0) { NJSON_SET(M); } else
#define NJSON_SERIALIZE_SUPER_CLASS(S) _NJSON_SERIALIZE_SUPER_CLASS((S *)this,njson_val)
#define NJSON_DESERIALIZE_SUPER_CLASS(S) _NJSON_DESERIALIZE_SUPER_CLASS((S *)this,njson_val)

#define SET_IF(K, M) _NJSON_SET_IF_NOT_DEFAULT(_root_obj_,K,M)

#define NJSON_NSET(M) _NJSON_SET(njson_val,#M,njson_var.get_##M())
#define NJSON_NGET(M) _NJSON_GET(njson_val,#M,&(njson_var->get_##M()),_njson_tmp_val_)
#define NJSON_NSERIALIZE_SUPER_CLASS(S) _NJSON_SERIALIZE_SUPER_CLASS((S *)&njson_var,njson_val)
#define NJSON_NDESERIALIZE_SUPER_CLASS(S) _NJSON_DESERIALIZE_SUPER_CLASS((S *)njson_var,njson_val)

inline int cut_string(char *cstr, char c);

/*Return c-style string,free it afterwards*/
template<typename _T>
inline char *njson_serialize(const _T &res) {
    JSON_Value *doc = njson_support_serialize(res);

    char *s = json_serialize_to_string_pretty(doc);

    json_value_free(doc);

    return s;
}

template<typename T>
inline void njson_deserialize(T *res, const char *s) {
    JSON_Value *doc = json_parse_string(s);

    njson_support_deserialize(doc, res);

    json_value_free(doc);
}

inline int cut_string(char *cstr, char c) {
    int n = 0;
    bool cut = true;
    while (*cstr) {
        if (*cstr == c) {
            *cstr = '\0';
            if (!cut) {
                ++n;
                cut = true;
            }
        } else {
            cut = false;
        }

        ++cstr;
    }

    if (!cut)++n;

    return n;
}

#endif//_NJSON_DEF_H_