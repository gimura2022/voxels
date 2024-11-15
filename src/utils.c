#include <math.h>
#include "utils.h"

float vec3_length(Vec3 v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3_mulf(Vec3 v, float s) {
  return (Vec3) {
    v.x * s,
    v.y * s,
    v.z * s,
  };
}

Vec3 vec3_divf(Vec3 v, float s) {
  return vec3_mulf(v, 1.0 / s);
}

Vec3 vec3_norm(Vec3 v) {
  float length = vec3_length(v);
  return vec3_divf(v, length);
}
