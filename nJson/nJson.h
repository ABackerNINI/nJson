#pragma once

#ifndef _NJSON_NJSON_H_
#define _NJSON_NJSON_H_

#define _NJSON_IS_DEFAULT_VALUE ::njson_is_default_value
#define _NJSON_SET_VALUE ::njson_serialize
#define _NJSON_GET_VALUE ::njson_deserialize

#define _NJSON_SET_IF_NOT_DEFAULT(ROOT, K, M) if(!_NJSON_IS_DEFAULT_VALUE(M))_NJSON_SET_VALUE(ROOT,K,M)

#define _NJSON_SET(ROOT,K, M) _NJSON_SET_IF_NOT_DEFAULT(ROOT,K,M)

#define _NJSON_GET(ROOT,K, M) if(json_object_has_value(json_value_get_object(ROOT),K)) \
    _NJSON_GET_VALUE(json_object_get_value(json_value_get_object(ROOT),K),M)

#define _NJSON_SERIALIZE_SUPER_CLASS(SUPER, ROOT) _NJSON_SET_VALUE(ROOT,NULL,*(SUPER))
#define _NJSON_DESERIALIZE_SUPER_CLASS(SUPER, ROOT) _NJSON_GET_VALUE(ROOT,SUPER)

#include "support/support_base.h"
#include "support/basic_type.h"
#include "support/cstr_type.h"
#include "support/string_type.h"

#include "support/list_type.h"
#include "support/vector_type.h"
#include "support/map_type.h"
#include "support/pointer_type.h"

#endif//_NJSON_NJSON_H_