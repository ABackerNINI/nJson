# Files tree

``` c
nJson─┬─nJson─┬─parson─┬─parson.c
      │       │        └─parson.h
      │       ├─support─┬─basic_type.h
      │       │         ├─cstr_type.h
      │       │         ├─list_type.h
      │       │         ├─map_type.h
      │       │         ├─pointer_type.h
      │       │         ├─string_to.h
      │       │         ├─string_type.h
      │       │         ├─to_string.h
      │       │         └─userdef_type.h
      │       ├─DEF.h
      │       ├─makefile
      │       ├─nJson.h
      │       └─parson.h
      ├─resource─┬─InnerRes.h
      │          └─Res.h
      └─main.cpp
```

## [nJson/parson](https://github.com/ABackerNINI/nJson/tree/master/nJson/parson)

Parson files.

## [nJson/support](https://github.com/ABackerNINI/nJson/tree/master/nJson/support)

Support the serialization/deserialization of ordinary types.

## [nJson/DEF.h](https://github.com/ABackerNINI/nJson/blob/master/nJson/DEF.h)

Define some definitions and functions that make enabling the serialization of a structure/class easily based on nJson.h. ___DEFINE YOUR OWN IF NEEDED___.

## [main.cpp](https://github.com/ABackerNINI/nJson/blob/master/main.cpp)

Test examples.
