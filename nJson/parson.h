#pragma once

#ifndef _UTILITIES_JSON_PARSON_H_
#define _UTILITIES_JSON_PARSON_H_

#include "parson/parson.h"

/*
 * Declarations:
 * */

/*json_object_set*/
inline void json_object_set(JSON_Object *obj,const char *key,char val);
inline void json_object_set(JSON_Object *obj,const char *key,bool val);
inline void json_object_set(JSON_Object *obj,const char *key,short val);
inline void json_object_set(JSON_Object *obj,const char *key,int val);
inline void json_object_set(JSON_Object *obj,const char *key,const char *val);
inline void json_object_set(JSON_Object *obj,const char *key,const float &val);
inline void json_object_set(JSON_Object *obj,const char *key,const long long &val);
inline void json_object_set(JSON_Object *obj,const char *key,const double &val);

/*json_array_append*/
inline void json_array_append(JSON_Array *arr,char val);
inline void json_array_append(JSON_Array *arr,bool val);
inline void json_array_append(JSON_Array *arr,short val);
inline void json_array_append(JSON_Array *arr,int val);
inline void json_array_append(JSON_Array *arr,const char *val);
inline void json_array_append(JSON_Array *arr,const float &val);
inline void json_array_append(JSON_Array *arr,const long long &val);
inline void json_array_append(JSON_Array *arr,const double &val);

/*json_object_get*/
template<typename _T>
inline _T json_object_get(const JSON_Object *obj, const char *key);

template<>
inline char json_object_get<char>(const JSON_Object *obj, const char *key){
	const char *s = json_object_get_string(obj,key);
	if(s)return s[0];
	return 0;
}
template<>
inline bool json_object_get<bool>(const JSON_Object *obj, const char *key){
	return json_object_get_boolean(obj,key)==1;
}
template<>
inline short json_object_get<short>(const JSON_Object *obj, const char *key){
	return (short)json_object_get_number(obj,key);
}
template<>
inline int json_object_get<int>(const JSON_Object *obj, const char *key){
	return (int)json_object_get_number(obj,key);
}
template<>
inline const char *json_object_get<const char *>(const JSON_Object *obj, const char *key){
	return json_object_get_string(obj,key);
}
template<>
inline float json_object_get<float>(const JSON_Object *obj, const char *key){
	return (float)json_object_get_number(obj,key);
}
template<>
inline long long json_object_get<long long>(const JSON_Object *obj, const char *key){
	return (long long)json_object_get_number(obj,key);
}
template<>
inline double json_object_get<double>(const JSON_Object *obj, const char *key){
	return json_object_get_number(obj,key);
}

/*json_array_get*/
template<typename _T>
inline _T json_array_get(const JSON_Array *arr, size_t index);

template<>
inline char json_array_get<char>(const JSON_Array *arr, size_t index){
	const char *s = json_array_get_string(arr,index);
	if(s)return s[0];
	return 0;
}
template<>
inline bool json_array_get<bool>(const JSON_Array *arr, size_t index){
	return json_array_get_boolean(arr,index)==1;
}
template<>
inline short json_array_get<short>(const JSON_Array *arr, size_t index){
	return (short)json_array_get_number(arr,index);
}
template<>
inline int json_array_get<int>(const JSON_Array *arr, size_t index){
	return (int)json_array_get_number(arr,index);
}
template<>
inline const char *json_array_get<const char *>(const JSON_Array *arr, size_t index){
	return json_array_get_string(arr,index);
}
template<>
inline float json_array_get<float>(const JSON_Array *arr, size_t index){
	return (float)json_array_get_number(arr,index);
}
template<>
inline long long json_array_get<long long>(const JSON_Array *arr, size_t index){
	return (long long)json_array_get_number(arr,index);
}
template<>
inline double json_array_get<double>(const JSON_Array *arr, size_t index){
	return json_array_get_number(arr,index);
}

/*
 * Definitions:
 * */

/*json_object_set*/
inline void json_object_set(JSON_Object *obj,const char *key,char val){
	char tmp[2];
	tmp[0] = val;
	tmp[1] = '\0';
	json_object_set_string(obj,key,tmp);
}
inline void json_object_set(JSON_Object *obj,const char *key,bool val){
	json_object_set_boolean(obj,key,val);
}
inline void json_object_set(JSON_Object *obj,const char *key,short val){
	json_object_set_number(obj,key,val);
}
inline void json_object_set(JSON_Object *obj,const char *key,int val){
	json_object_set_number(obj,key,val);
}
inline void json_object_set(JSON_Object *obj,const char *key,const char * val){
	json_object_set_string(obj,key,val);
}
inline void json_object_set(JSON_Object *obj,const char *key,const float &val){
	json_object_set_number(obj,key,val);
}
inline void json_object_set(JSON_Object *obj,const char *key,const long long &val){
	json_object_set_number(obj,key,val);
}
inline void json_object_set(JSON_Object *obj,const char *key,const double &val){
	json_object_set_number(obj,key,val);
}

/*json_array_append*/
inline void json_array_append(JSON_Array *arr,char val){
	char tmp[2];
	tmp[0] = val;
	tmp[1] = '\0';
	json_array_append_string(arr,tmp);
}
inline void json_array_append(JSON_Array *arr,bool val){
	json_array_append_boolean(arr,val);
}
inline void json_array_append(JSON_Array *arr,short val){
	json_array_append_number(arr,val);
}
inline void json_array_append(JSON_Array *arr,int val){
	json_array_append_number(arr,val);
}
inline void json_array_append(JSON_Array *arr,const char *val){
	json_array_append_string(arr,val);
}
inline void json_array_append(JSON_Array *arr,const float &val){
	json_array_append_number(arr,val);
}
inline void json_array_append(JSON_Array *arr,const long long &val){
	json_array_append_number(arr,val);
}
inline void json_array_append(JSON_Array *arr,const double &val){
	json_array_append_number(arr,val);
}

/*json_object_get*/
// char json_object_get(const JSON_Object *object, const char *key,char){
// 	printf("%s\n", key);
// 	const char *s = json_object_get_string(object,key);
// 	if(s)return s[0];
// 	return 0;
// }
// bool json_object_get(const JSON_Object *object, const char *key,bool){
// 	return json_object_get_boolean(object,key)==1;
// }
// short json_object_get(const JSON_Object *object, const char *key,short){
// 	return (short)json_object_get_number(object,key);
// }
// int json_object_get(const JSON_Object *object, const char *key,int){
// 	return (int)json_object_get_number(object,key);
// }
// const char *json_object_get(const JSON_Object *object, const char *key,const char *){
// 	return json_object_get_string(object,key);
// }
// float json_object_get(const JSON_Object *object, const char *key,float){
// 	return (float)json_object_get_number(object,key);
// }
// long long json_object_get(const JSON_Object *object, const char *key,long long){
// 	return (long long)json_object_get_number(object,key);
// }
// double json_object_get(const JSON_Object *object, const char *key,double){
// 	return json_object_get_number(object,key);
// }

// char json_array_get(const JSON_Array *arr, size_t index,char){
// 	const char *s = json_array_get_string(arr,index);
// 	if(s)return s[0];
// 	return 0;
// }
// bool json_array_get(const JSON_Array *arr,size_t index,bool){
// 	return json_array_get_boolean(arr,index)==1;
// }
// short json_array_get(const JSON_Array *arr, size_t index,short){
// 	return (short)json_array_get_number(arr,index);
// }
// int json_array_get(const JSON_Array *arr,size_t index,int){
// 	return (int)json_array_get_number(arr,index);
// }
// const char *json_array_get(const JSON_Array *arr, size_t index,const char *){
// 	return json_array_get_string(arr,index);
// }
// float json_array_get(const JSON_Array *arr, size_t index,float){
// 	return (float)json_array_get_number(arr,index);
// }
// long long json_array_get(const JSON_Array *arr, size_t index,long long){
// 	return (long long)json_array_get_number(arr,index);
// }
// double json_array_get(const JSON_Array *arr, size_t index,double){
// 	return (double)json_array_get_number(arr,index);
// }

#endif//_UTILITIES_JSON_PARSON_H_