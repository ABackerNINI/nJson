cc = g++
cflags = -std=gnu++0x -Wall -W
bin_dir = build
obj_dir = build/obj

all: pre $(bin_dir)/out

pre:
	test -d $(bin_dir) || mkdir -p $(bin_dir)
	test -d $(obj_dir) || mkdir -p $(obj_dir)

$(obj_dir)/parson.o: nJson/parson/parson.h nJson/*.h nJson/support/*.h nJson/type_traits/*.h
	$(cc) $(cflags) -c nJson/parson/parson.c -o $(obj_dir)/parson.o

$(obj_dir)/main.o: main.cpp resource/Res.h
	$(cc) $(cflags) -c main.cpp -o $(obj_dir)/main.o

$(bin_dir)/out: $(obj_dir)/main.o $(obj_dir)/parson.o
	$(cc) $(cflags) -o $(bin_dir)/out $^

clean:
	rm -rf $(bin_dir)

.PHONY: pre all clean
