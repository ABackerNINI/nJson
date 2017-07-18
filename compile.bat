g++ -c nJson/parson/parson.c -o parson.o -std=gnu++0x

g++ main.cpp parson.o -o out -std=gnu++0x

out.exe