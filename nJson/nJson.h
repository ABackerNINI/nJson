#pragma once

#ifndef _UTILITIES_JSON_JSON_H_
#define _UTILITIES_JSON_JSON_H_

#define _SET_VALUE njson_set_value
#define _IS_DEFAULT_VALUE is_default_value
#define _SET_IF_NOT_DEFAULT(ROOT,K,M) if(!_IS_DEFAULT_VALUE(M))_SET_VALUE(ROOT,K,M)
#define _SET(ROOT,M) _SET_IF_NOT_DEFAULT(ROOT,#M,M)

#define _GET_VALUE njson_get_value
#define _GET(ROOT,M) _GET_VALUE(ROOT,#M,&M)

#define _SERIALIZE_SUPER_CLASS(S) S::serialize
#define _DESERIALIZE_SUPER_CLASS(S) S::deserialize

#include "support/basic_type.h"
#include "support/cstr_type.h"
#include "support/string_type.h"
#include "support/list_type.h"
#include "support/map_type.h"
#include "support/userdef_type.h"

/*
	Includes "support/pointer_type.h" after other type-support files to support their corresponding pointer types.
	So how to support the pointer types of other types? I haven't figured out.
*/
#include "support/pointer_type.h"

#endif//_UTILITIES_JSON_JSON_H_