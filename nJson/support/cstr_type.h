#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_CSTR_TYPE_H_
#define _UTILITIES_JSON_SUPPORT_CSTR_TYPE_H_

#include "../parson.h"

/*
	This file is to support the serialization and deserialization of type 'char *'.
	Note that this file support the char pointers point to a char array contains no less than two chars.
*/

/*Feature 'strdup' will malloc and copy c-style strings from json-object,that means you need to free it manually afterwards.*/
#define FEATURE_STRDUP							1

#define DEFAULT_VALUE_CSTR						NULL

/*
 * Declarations:
 * */

inline bool is_default_value(const char *val);

inline void njson_set_value(JSON_Object *obj,const char *key,const char *val);
inline void njson_set_value(JSON_Array *arr,const char *val);

inline void njson_get_value(JSON_Object *obj,const char *key,const char **val);
inline void njson_get_value(JSON_Array *arr,size_t index,const char **val);

/*
 * Definitions:
 * */

/*is_default_value*/
inline bool is_default_value(const char *val){
	return val==DEFAULT_VALUE_CSTR;
}

/*njson_set_value*/
inline void njson_set_value(JSON_Object *obj,const char *key,const char *val){
	json_object_set(obj,key,val);
}
inline void njson_set_value(JSON_Array *arr,const char *val){
	json_array_append(arr,val);
}

/*njson_get_value*/
inline void njson_get_value(JSON_Object *obj,const char *key,const char **val){
	if(json_object_has_value(obj,key)){
		*val = json_object_get<const char *>(obj,key);

#if(FEATURE_STRDUP)
		*val = strdup(*val);
#endif
	}
}
inline void njson_get_value(JSON_Array *arr,size_t index,const char **val){
	*val = json_array_get<const char *>(arr,index);

#if(FEATURE_STRDUP)
	*val = strdup(*val);
#endif
}

#endif//_UTILITIES_JSON_SUPPORT_CSTR_TYPE_H_