#pragma once

#ifndef _NJSON_SUPPORT_USER_DEFINE_TYPE_H_
#define _NJSON_SUPPORT_USER_DEFINE_TYPE_H_

#include "../parson/parson.h"

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

template<typename T>
inline bool njson_is_default_value(const T &njson_var);

template<typename T>
inline JSON_Value *njson_serialize(const T &njson_var);

template<typename T>
inline void njson_deserialize(JSON_Value *njson_val, T *njson_var);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename _T>
inline bool njson_is_default_value(const _T &njson_var) {
    return false;//return res.isUninitialized();
}

template<typename T>
inline JSON_Value *njson_serialize(const T &njson_var) {
    return njson_var.njson_serialize();
}

template<typename T>
inline void njson_deserialize(JSON_Value *njson_val, T *njson_var) {
    njson_var->njson_deserialize(njson_val);
}

#endif//_NJSON_SUPPORT_USER_DEFINE_TYPE_H_