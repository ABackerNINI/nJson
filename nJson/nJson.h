#pragma once

#ifndef _NJSON_NJSON_H_
#define _NJSON_NJSON_H_

#define _SET_VALUE ::njson_serialize
#define _IS_DEFAULT_VALUE ::njson_is_default_value
#define _SET_IF_NOT_DEFAULT(ROOT, K, M) if(!_IS_DEFAULT_VALUE(M))           \
    json_object_set_value(json_value_get_object(ROOT),K,_SET_VALUE(M))

#define _SET(ROOT, M) _SET_IF_NOT_DEFAULT(ROOT,#M,M)

#define _GET_VALUE ::njson_deserialize
#define _GET(ROOT, M) _GET_VALUE(json_object_get_value(json_value_get_object(ROOT),#M),&(M))

#define _SERIALIZE_SUPER_CLASS(S) S::serialize
#define _DESERIALIZE_SUPER_CLASS(S) S::deserialize

#include "support/basic_type.h"
#include "support/cstr_type.h"
#include "support/string_type.h"

/* Template types support files.
 * You need to rearrange the include order of these files to support some special nesting types.
 * For example,include "list_type.h" and then include "map_type.h",
 * the following types are supported:
 *      list<T>,
 *      map<T1,T2>,
 *      list<list<T>>,
 *      map<T1,list<T2>>,
 *      map<T1,list<T2>>,
 *      and some other nesting types exclude "list<map<T1,T2>>".
 * To support "list<map<T1,T2>>",include "list_type.h" after "map_type.h".
 * */
#include "support/list_type.h"
#include "support/map_type.h"
#include "support/userdef_type.h"
/*
	Includes "support/pointer_type.h" after other type-support files to support their corresponding pointer types.
	So how to support the pointer types of other types? I haven't figured out.
*/
#include "support/pointer_type.h"

#endif//_NJSON_NJSON_H_