#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_TO_STRING_H_
#define _UTILITIES_JSON_SUPPORT_TO_STRING_H_

#include <string>
#include "../parson.h"

/*
	This file is to support the serialization of type 'std::map<_T1,_T2>'
	implements std::string to_string(_T1) and void add_key_value(JSON_Object *,const char *,_T2)
	to support std::map<_T1,_T2>
*/

/*
 * Declarations:
 * */

/*to_string*/
inline std::string to_string(char val);
inline std::string to_string(bool val);
inline std::string to_string(short val);
inline std::string to_string(int val);
inline std::string to_string(const char *val);
inline std::string to_string(float val);
inline std::string to_string(long long val);
inline std::string to_string(double val);
inline const std::string &to_string(const std::string &val);

/*
 * Definitions:
 * */

/*to_string*/
inline std::string to_string(char val){
	char tmp[2];
	tmp[0] = val;
	tmp[1] = '\0';

	return std::string(tmp);
}
inline std::string to_string(bool val){
	return val?std::string("true"):std::string("false");
}
inline std::string to_string(short val){
	char tmp[10];
	sprintf(tmp,"%d",val);
	return tmp;
}
inline std::string to_string(int val){
	char tmp[15];
	sprintf(tmp,"%d",val);
	return tmp;
}
inline std::string to_string(const char *val){
	return std::string(val);
}
inline std::string to_string(float val){
	char tmp[25];
	sprintf(tmp,"%f",val);
	return tmp;
}
inline std::string to_string(long long val){
	char tmp[25];
	sprintf(tmp,"%lld",val);
	return tmp;
}
inline std::string to_string(double val){
	char tmp[30];
	sprintf(tmp,"%lf",val);
	return tmp;
}
inline const std::string &to_string(const std::string &val){
	return val;
}

#endif//_UTILITIES_JSON_SUPPORT_TO_STRING_H_