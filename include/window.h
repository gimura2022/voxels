#include <GLFW/glfw3.h>

typedef struct {
  GLFWwindow *window;
  int width, height;
  bool polygon_mode;
} Window;

Window createWindow(int width, int height);
int initWindow(Window* window);
void getWindowSize(Window* window, int *width, int *height);
void swapBuffer(Window* window);
bool windowShouldClose(Window* window);
void getCursorPos(Window* window, double *xpos, double *ypos);