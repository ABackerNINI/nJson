#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_USER_DEFINE_TYPE_H_
#define _UTILITIES_JSON_SUPPORT_USER_DEFINE_TYPE_H_

#include "../parson.h"

/*
	This file is to support the serialization and deserialization of user-defined types.
	user-defined types are composite types (structs or classes) which implement functions:
  		JSON_Value *serialize() const;
  		void deserialize(JSON_Value *doc);
  	user-defined types can only consist of types supported by files:
		basic_type.h
		list_type.h
		map_type.h (with to_string.h and string_to.h)
		pointer_type.h
		string_type.h
		userdef_type.h
*/

template<typename _T>
inline bool is_default_value(const _T &res){
	return false;//return res.isUninitialized();
}

template<typename _T>
inline void set_key_value(JSON_Object *obj,const char *key,const _T &res){
	JSON_Value *doc = json_value_init_object();
	res.serialize(doc);
	json_object_set_value(obj,key,doc);
}
template<typename _T>
inline void set_key_value(JSON_Array *arr,const _T &res){
	JSON_Value *doc = json_value_init_object();
	res.serialize(doc);
	json_array_append_value(arr,doc);
}

template<typename _T>
inline void get_value(JSON_Object *obj,const char *key,_T *res){
	if(json_object_has_value(obj,key))
		res->deserialize(json_object_get_value(obj,key));
}
template<typename _T>
inline void get_value(JSON_Array *arr,size_t index,_T *res){
	res->deserialize(json_array_get_value(arr,index));
}

#endif//_UTILITIES_JSON_SUPPORT_USER_DEFINE_TYPE_H_