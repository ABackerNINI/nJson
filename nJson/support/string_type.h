#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_STRING_TYPE_H_
#define _UTILITIES_JSON_SUPPORT_STRING_TYPE_H_

#include <string>
#include "../parson.h"

/*
	This file is to support the serialization and deserialization of type 'std::string'.
*/

/*
 * Declarations:
 * */

inline bool is_default_value(const std::string &val);

inline void njson_set_value(JSON_Object *obj,const char *key,const std::string &val);
inline void njson_set_value(JSON_Array *arr,const std::string &val);

inline void njson_get_value(JSON_Object *obj,const char *key,std::string *val);
inline void	njson_get_value(JSON_Array *arr,size_t index,std::string *val);

/*
 * Definitions:
 * */

/*is_default_value*/
inline bool is_default_value(const std::string &val){
	return val.size()==0;
}

/*njson_set_value*/
inline void njson_set_value(JSON_Object *obj,const char *key,const std::string &val){
	json_object_set(obj,key,val.c_str());
}
inline void njson_set_value(JSON_Array *arr,const std::string &val){
	json_array_append(arr,val.c_str());
}

/*njson_get_value*/
inline void njson_get_value(JSON_Object *obj,const char *key,std::string *val){
	if(json_object_has_value(obj,key)){
		const char *s;
		s = json_object_get<const char *>(obj,key);
		if(s)*val = s;
	}
}
inline void	njson_get_value(JSON_Array *arr,size_t index,std::string *val){
	const char *s;
	s = json_array_get<const char *>(arr,index);
	if(s)*val = s;
}

#endif//_UTILITIES_JSON_SUPPORT_STRING_TYPE_H_