#pragma once

#ifndef _NJSON_DEF_H_
#define _NJSON_DEF_H_

#include "nJson.h"

#define NJSON_SET(M) _NJSON_SET(njson_val,#M,M)
#define NJSON_SET_AS_TYPE(M, T) _NJSON_SET(njson_val,#M,(T)(M))
#define NJSON_GET(M) _NJSON_GET(njson_val,#M,&(M))
#define NJSON_GET_AS_TYPE(M, T) _NJSON_GET(njson_val,#M,(T *)(&(M)))

#define NJSON_SET_IF_KEY(M) if(strcmp(#M,_key_) == 0) { NJSON_SET(M); } else
#define NJSON_SERIALIZE_SUPER_CLASS(S) _NJSON_SERIALIZE_SUPER_CLASS((S *)this,njson_val)
#define NJSON_DESERIALIZE_SUPER_CLASS(S) _NJSON_DESERIALIZE_SUPER_CLASS((S *)this,njson_val)

#define SET_IF(K, M) _NJSON_SET_IF_NOT_DEFAULT(_root_obj_,K,M)

inline int cut_string(char *cstr, char c);

//template<typename _T>
//inline JSON_Value *serialize_to_doc(const _T &res, char *keys = NULL) {
//    JSON_Value *doc = json_value_init_object();
//
//    if (keys) {
//        bool cut = true;
//        int n = cut_string(keys, ',');
//        if (n > 0) {
//            for (char *key = keys; n > 0; ++key) {
//                if (*key == '\0') {
//                    cut = true;
//                } else if (cut) {
//                    res.njson_serialize(doc, key);
//                    --n;
//                    cut = false;
//                }
//            }
//        } else res.njson_serialize();
//    } else res.njson_serialize();
//
//    return doc;
//}

/*Return c-style string,free it afterwards*/
template<typename _T>
inline char *njson_serialize(const _T &res) {
    JSON_Value *doc = json_value_init_object();

    njson_serialize(doc, NULL, res);

    char *s = json_serialize_to_string_pretty(doc);

    json_value_free(doc);

    return s;
}

template<typename T>
inline void njson_deserialize(T *res, const char *s) {
    JSON_Value *doc = json_parse_string(s);

    njson_deserialize(doc, res);

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