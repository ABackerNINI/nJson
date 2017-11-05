cmake_minimum_required(VERSION 3.6)
project(CRMS_On_VxWOrks)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

##############################################################################################

set(NJSON_FILE_TREE
        nJson/parson/parson.c
        nJson/parson/parson.h
        nJson/support/basic_type.h
        nJson/support/cstr_type.h
        nJson/support/list_type.h
        nJson/support/map_type.h
        nJson/support/pointer_type.h
        nJson/support/string_type.h
        nJson/support/userdef_type.h
        nJson/DEF.h
        nJson/nJson.h
        )

set(RESOURCE
#        resource/InnerRes.h
#        resource/Res.h
        )

add_executable(nJson main.cpp
        ${NJSON_FILE_TREE}
        ${RESOURCE}
        )
