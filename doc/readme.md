## Files tree
```
nJson─┬─doc─┬─readme.md
      │     └─foo.md
      ├─nJson─┬─parson─┬─parson.c
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
      ├─.gitignore
      ├─compile.bat
      ├─LICENSE
      ├─main.cpp
      ├─makefile
      └─readme.md
```

## "[doc](https://github.com/ABackerNINI/nJson/tree/master/doc)"
### "[doc/readme.md](https://github.com/ABackerNINI/nJson/blob/master/doc/readme.md)"(this file)
This file introduces most folders/files briefly.

## "[nJson](https://github.com/ABackerNINI/nJson/tree/master/nJson)"
Source file of "nJson" lib.
### "[nJson/parson](https://github.com/ABackerNINI/nJson/tree/master/nJson/parson)"
Parson files.
### "[nJson/support](https://github.com/ABackerNINI/nJson/tree/master/nJson/support)"
Support the serialization/deserialization of odinary types.
### "[nJson/DEF.h](https://github.com/ABackerNINI/nJson/blob/master/nJson/DEF.h)"
Define some definations and functions that make enabling the serialization of a structure/calss easily based on nJson.h. ___DEFINE YOUR OWN IF NEEDED___.

## "[resource](https://github.com/ABackerNINI/nJson/tree/master/resource)"
Example resources.

## "[.gitignore](https://github.com/ABackerNINI/nJson/blob/master/.gitignore)"
Gitignore.

## "[compile.bat](https://github.com/ABackerNINI/nJson/blob/master/compile.bat)"
Bat file that compile and run main.cpp.

## "[main.cpp](https://github.com/ABackerNINI/nJson/blob/master/main.cpp)"
Test Example resources.

## "[makefile](https://github.com/ABackerNINI/nJson/blob/master/makefile)"
Makefile that compile and run main.cpp
