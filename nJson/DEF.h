#pragma once

#ifndef _NJSON_DEF_H_
#define _NJSON_DEF_H_

#include "nJson.h"

#define SET(M) _SET(njson_val,M)
#define GET(M) _GET(njson_val,M)
#define SET_IF_KEY(M) if(strcmp(#M,_key_) == 0) { SET(M); } else
#define SERIALIZE_SUPER_CLASS(S) _SERIALIZE_SUPER_CLASS((S *)this,njson_val)
#define DESERIALIZE_SUPER_CLASS(S) _DESERIALIZE_SUPER_CLASS((S *)this,njson_val)

#define SET_IF(K, M) _SET_IF_NOT_DEFAULT(_root_obj_,K,M)

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
inline char *serialize(const _T &res) {
    JSON_Value *doc = json_value_init_object();

    njson_serialize(doc, NULL, res);

    char *s = json_serialize_to_string_pretty(doc);

    json_value_free(doc);

    return s;
}

template<typename T>
inline void deserialize(T *res, const char *s) {
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