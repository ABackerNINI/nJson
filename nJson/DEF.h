#pragma once

#ifndef _NJSON_DEF_H_
#define _NJSON_DEF_H_

#include "nJson.h"

#define NJSON_VAL njson_val
#define NJSON_VAR njson_var
#define NJSON_TMP_VAL _njson_tmp_val_

#define NJSON_SERIALIZE_INIT _NJSON_SERIALIZE_INIT(NJSON_VAL)
#define NJSON_DESERIALIZE_INIT _NJSON_DESERIALIZE_INIT(NJSON_TMP_VAL)
#define NJSON_RET return njson_val

#define NJSON_SET(M) _NJSON_SET(NJSON_VAL,#M,M)
#define NJSON_GET(M) _NJSON_GET(NJSON_VAL,#M,&(M),NJSON_TMP_VAL)
#define NJSON_SET_AS_TYPE(M, T) _NJSON_SET(NJSON_VAL,#M,(T)(M))
#define NJSON_GET_AS_TYPE(M, T) _NJSON_GET(NJSON_VAL,#M,(T *)(&(M)))

#define NJSON_SERIALIZE_SUPER_CLASS(S) _NJSON_SERIALIZE_SUPER_CLASS((S *)this,NJSON_VAL)
#define NJSON_DESERIALIZE_SUPER_CLASS(S) _NJSON_DESERIALIZE_SUPER_CLASS((S *)this,NJSON_VAL)

#define NJSON_NSET(M) _NJSON_SET(NJSON_VAL,#M,NJSON_VAR.get_##M())
#define NJSON_NGET(M) _NJSON_GET(NJSON_VAL,#M,&(NJSON_VAR->get_##M()),NJSON_TMP_VAL)
#define NJSON_NSERIALIZE_SUPER_CLASS(S) _NJSON_SERIALIZE_SUPER_CLASS((S *)&NJSON_VAR,NJSON_VAL)
#define NJSON_NDESERIALIZE_SUPER_CLASS(S) _NJSON_DESERIALIZE_SUPER_CLASS((S *)NJSON_VAR,NJSON_VAL)

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