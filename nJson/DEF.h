#pragma once

#ifndef _NJSON_DEF_H_
#define _NJSON_DEF_H_

#include "nJson.h"

#define SET(M) _SET(_root_obj_,M)
#define GET(M) _GET(_root_obj_,M)
#define SET_IF_KEY(M) if(strcmp(#M,_key_) == 0) { SET(M); } else
#define SERIALIZE_SUPER_CLASS(S) _SERIALIZE_SUPER_CLASS(S)(_doc_,_key_)
#define DESERIALIZE_SUPER_CLASS(S) _DESERIALIZE_SUPER_CLASS(S)(_doc_)

#define SET_IF(K,M) _SET_IF_NOT_DEFAULT(_root_obj_,K,M)

inline int cut_string(char *cstr);

/*Return c-style string,free it afterwards*/
template<typename _T>
inline const char *serialize(const _T &res,char *keys = NULL){
	JSON_Value *doc = json_value_init_object();

	if(keys){
		bool cut = true;
		int n = cut_string(keys);
		if(n>0){
			for(char *key = keys;n>0;++key){
				if(*key=='\0'){
					cut=true;
				} else if(cut) {
					res.serialize(doc,key);
					--n;
					cut = false;
				}
			}
		} else res.serialize(doc);
	} else res.serialize(doc);

	const char *s = json_serialize_to_string_pretty(doc);

	json_value_free(doc);

	return s;
}

template<typename _T>
inline void deserialize(_T *res, const char *s){
	JSON_Value *doc =json_parse_string(s);
	res->deserialize(doc);

	json_value_free(doc);
}

inline int cut_string(char *cstr){
	int n = 0;
	bool cut = true;
	while(*cstr){
		if(*cstr==' '){
			*cstr = '\0';
			if(!cut){
				++n;
				cut = true;
			}
		} else {
			cut = false;
		}

		++cstr;
	}

	if(!cut)++n;

	return n;
}

#endif//_NJSON_DEF_H_