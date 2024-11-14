#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

#include "../include/window.h"
#include "../include/shader.h"
#include "../include/logs.h"

void swapBuffer(Window *window) {
  glfwSwapBuffers(window->window);
}

bool windowShouldClose(Window *window) {
  return glfwWindowShouldClose(window->window);
}

void getCursorPos(Window *window, double *xpos, double *ypos) {
  glfwGetCursorPos(window->window, xpos, ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  } else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    Window *my_window = glfwGetWindowUserPointer(window);
    my_window->polygon_mode = !my_window->polygon_mode;
    if (my_window->polygon_mode) {
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }
}

void resize_callback(GLFWwindow* window, int new_width, int new_height) {
  Window *my_window = glfwGetWindowUserPointer(window);
  my_window->width = new_width;
  my_window->height = new_height;
  glViewport(0, 0, new_width, new_height);
}

Window createWindow(int width, int height) {
  return (Window) {
    NULL,
    width,
    height,
    false,
  };
}

int initWindow(Window* window) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, true);
  info("GLFW был инициализирован");

  window->window = glfwCreateWindow(window->width, window->height, "Voxels", NULL, NULL);
  if (window->window == NULL) {
    error("Не удалось создать GLFW окно");
    return -1;
  }
  info("Окно было инициализировано");

  glfwSetWindowUserPointer(window->window, window);

  glfwGetFramebufferSize(window->window, &window->width, &window->height);

  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwMakeContextCurrent(window->window);
  info("Контекст OpenGL был привязан к окну");

  if (!glewInit()) {
    error("Не удалось инициализировать GLEW");
    glfwTerminate();
    return -1;
  }
  info("GLEW был инициализирован");

  glfwSetKeyCallback(window->window, key_callback);
  info("Функция key_callback отлавливает пользовательский ввод");

  glfwSetFramebufferSizeCallback(window->window, resize_callback);
  info("Функция resize_callback отлавливает изменения размера окна");

  return 0;
}
