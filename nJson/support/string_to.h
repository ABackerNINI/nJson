#pragma once

#ifndef _UTILITIES_JSON_SUPPORT_STRING_TO_H_
#define _UTILITIES_JSON_SUPPORT_STRING_TO_H_

#include <string>
#include <stdlib.h>
#include "../parson.h"

/*
	This file is to support the deserialization of type 'std::map<_T1,_T2>'.
	implements:
		void string_to(const char *,_T1);
		void get_val(JSON_Object *,const char *,_T2 *);
	to support std::map<_T1,_T2>.
*/

/*
 * Declarations:
 * */

/*string_to*/
inline void string_to(const char *s,char *val);
inline void string_to(const char *s,bool *val);
inline void string_to(const char *s,short *val);
inline void string_to(const char *s,int *val);
inline void string_to(const char *s,float *val);
inline void string_to(const char *s,long long *val);
inline void string_to(const char *s,double *val);
inline void string_to(const char *s,std::string *val);

/*
 * Definitions:
 * */

/*string_to*/
inline void string_to(const char *s,char *val){
	*val = s[0];
}
inline void string_to(const char *s,bool *val){
	*val = (strcmp(s,"true") == 0);
}
inline void string_to(const char *s,short *val){
	*val = (short)atoi(s);
}
inline void string_to(const char *s,int *val){
	*val = atoi(s);
}
inline void string_to(const char *s,float *val){
	*val = (float)atof(s);
}
inline void string_to(const char *s,long long *val){
	*val = atoll(s);
}
inline void string_to(const char *s,double *val){
	*val = atof(s);
}
inline void string_to(const char *s,std::string *val){
	*val = std::string(s);
}

#endif//_UTILITIES_JSON_SUPPORT_STRING_TO_H_