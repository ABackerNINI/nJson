#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_POINTER_TYPE_H_
#define _UTILITIES_JSON_SUPPORT_POINTER_TYPE_H_

#include "../parson.h"

#define DEFAULT_VALUE_POINTER NULL

/*
	This file is to support the serialization and deserialization of pointer type.
	implements:
		bool is_default_value(_T *)
		void njson_set_value(JSON_Object *,const char *,const _T &);
		void njson_set_value(JSON_Array *,const _T &);
		void njson_get_value(JSON_Object *,const char *,_T *);
		void njson_get_value(JSON_Array *,size_t index,_T *);
	to support type '_T' and '*_T' along with '**_T' and '(n*)_T'.

	Note that you need to implement your own functions to support pointers point to array.
	See 'cstr_type.h' for reference.
*/

template<typename _T>
inline bool is_default_value(_T *val){
	return val == DEFAULT_VALUE_POINTER || is_default_value(*val);
}

template<typename _T>
inline void njson_set_value(JSON_Object *obj,const char *key, _T * const res){
	njson_set_value(obj,key,*res);
}
template<typename _T>
inline void njson_set_value(JSON_Array *arr, _T * const res){
	njson_set_value(arr,*res);
}

template<typename _T>
inline void njson_get_value(JSON_Object *obj,const char *key,_T **res){
	if(json_object_has_value(obj,key)){
		*res = new _T();
		njson_get_value(obj,key,*res);
	}
}
template<typename _T>
inline void njson_get_value(JSON_Array *arr,size_t index,_T **res){
	*res = new _T();
	njson_get_value(arr,index,*res);
}

#endif//_UTILITIES_JSON_SUPPORT_POINTER_TYPE_H_