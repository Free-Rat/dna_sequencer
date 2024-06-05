all: build

build:
	gcc ./src/main.c -o ./build/main

run:
	cd ./build && ./main

zig:
	zig cc ./src/main.c -o ./build/main
	cd ./build && ./main
