run: build
	./build/voxels.out

build: src
	cc -o ./build/voxels.out src/*.c -lGLEW -lglfw -lGL -lm -I./include -std=c2x -Wall -Wextra -Wpedantic
