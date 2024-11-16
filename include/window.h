#include <GLFW/glfw3.h>

#include <stdbool.h>

#ifndef _window_h
#define _window_h
typedef struct {
	GLFWwindow *window;
	int width, height;
	bool keys[1024];
	bool polygon_mode;
} Window;

Window createWindow(int width, int height);
int initWindow(Window *window);
void getWindowSize(Window *window, int *width, int *height);
void swapBuffer(Window *window);
bool windowShouldClose(Window *window);
void getCursorPos(Window *window, double *xpos, double *ypos);
#endif // _window_h
