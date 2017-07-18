cc=g++
cflags='-std=gnu++0x'
root_dir=$(shell cd)
obj_dir=debug/obj
bin_dir=debug

all: parson.o main.o out.o
	$(bin_dir)/out.exe

parson.o: nJson/parson/parson.h
	$(cc) $(cflags) -c nJson/parson/parson.c -o $(obj_dir)/parson.o

main.o:
	$(cc) $(cflags) -c main.cpp -o $(obj_dir)/main.o

out.o: $(obj_dir)/main.o $(obj_dir)/parson.o
	$(cc) $(cflags) -o $(bin_dir)/out $^

clean:
	rd /S/Q $(root_dir)/$(obj_dir)
	del $(root_dir)/$(bin_dir)/*.exe

