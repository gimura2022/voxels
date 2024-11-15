#ifndef _utils
#define _utils
typedef struct {
  float x, y, z;
} Vec3;

float vec3_length(Vec3);
Vec3 vec3_mulff(Vec3, float);
Vec3 vec3_divf(Vec3, float);
Vec3 vec3_norm(Vec3);
#endif // _utils

