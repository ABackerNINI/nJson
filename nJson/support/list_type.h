#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_LIST_TYPE_H_
#define _UTILITIES_JSON_SUPPORT_LIST_TYPE_H_

#include <list>
#include "../parson.h"

/*
	This file is to support the serialization and deserialization of type 'std::list<_T>'.
*/

template<typename _T>
inline bool is_default_value(const std::list<_T> &val){
	return val.size()==0;
}

template<typename _T>
	   void njson_set_value(JSON_Object *obj,const char *key,const std::list<_T> &val){
			json_object_set_value(obj,key,json_value_init_array());
			JSON_Array *arr = json_object_get_array(obj,key);
			typename std::list<_T>::const_iterator it;
			for(it = val.begin();it!=val.end();++it){
				njson_set_value(arr,*it);
			}
	   }
template<typename _T>
	   void njson_set_value(JSON_Array *arr,const std::list<_T> &val){
	   		typename std::list<_T>::const_iterator it;
			for(it = val.begin();it!=val.end();++it){
				njson_set_value(arr,*it);
			}
	   }//implements to support std::list<std::list<_T> >

template<typename _T>
	   void njson_get_value(JSON_Object *obj,const char *key,std::list<_T> *val){
	   		JSON_Array *arr = json_object_get_array(obj,key);
	   		size_t n = json_array_get_count(arr);
	   		_T lval;
	   		for(size_t i=0;i<n;++i){
	   			njson_get_value(arr,i,&lval);
	   			val->push_back(lval);
	   		}
	   }
template<typename _T>
	   void njson_get_value(JSON_Array *arr,const std::list<_T> &val);//implements to support std::list<std::list<_T> >

#endif//_UTILITIES_JSON_SUPPORT_LIST_TYPE_H_