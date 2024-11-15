#include "utils.h"

typedef struct {
  Vec3 direction;
} Camera;

void camera_update(Camera *camera, bool keys[1024], float dt);
