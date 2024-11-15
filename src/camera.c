#include <GLFW/glfw3.h>

#include <math.h>
#include <stdbool.h>
#include "../include/camera.h"

void camera_update(Camera *camera, bool keys[1024], float dt) {
  int up = keys[GLFW_KEY_UP] - keys[GLFW_KEY_DOWN];
  int left = keys[GLFW_KEY_LEFT] - keys[GLFW_KEY_RIGHT];

  camera->direction.y += up * dt;
  camera->direction.x += left * dt;

  camera->direction.y = fmax(fmin(camera->direction.y, 1.0f), -1.0f);
}
