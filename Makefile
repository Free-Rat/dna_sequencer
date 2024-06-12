all: build

build:
	gcc ./src/main.c -o ./build/main

run:
	cd ./build && ./main

zig:
	zig cc ./src/main.c -o ./build/main
	cd ./build && ./main

com_zig:
	zig cc ./src/main.c -o ./build/main

time:
	gcc ./src/main.c -o ./build/main
	cd ./build && time ./main
