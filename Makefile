run: build
	./build/voxels.out

build: src
	cc -o ./build/voxels.out src/main.c src/logs.c src/window.c src/shader.c -lGLEW -lglfw -lGL -lm -std=c2x -Wall -Wextra -Wpedantic
