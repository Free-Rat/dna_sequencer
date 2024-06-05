all: build

build:
	gcc ./src/main.c -o ./build/main

run:
	cd ./build && ./main