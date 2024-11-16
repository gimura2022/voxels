#include "chunk.h"

#define Vectorize(type, name) typedef struct {\
  type *data;\
  unsigned int capacity;\
  unsigned int size;\
  unsigned int step;\
} name;\
name name##_init(unsigned int capacity, unsigned int step);\
void name##_append(name *vec, type value);

#ifdef _vector_impl
#include <stdlib.h>
#define VectorImpl(type, name) \
name name##_init(unsigned int capacity, unsigned int step) {\
  type *data = malloc(capacity * sizeof(type));\
  return (name) {\
    data,\
    capacity,\
    0,\
    step,\
  };\
}\
\
void name##_append(name *vec, type value) {\
  if (vec->size >= vec->capacity) {\
    vec->capacity += vec->step;\
    vec->data = realloc(vec->data, vec->capacity * sizeof(type));\
  }\
  vec->data[vec->size] = value;\
  vec->size++;\
}
#endif // _vector_impl

Vectorize(float, FloatVector)
Vectorize(unsigned int, UnsignedIntVector)


typedef struct {
  FloatVector vertices;
  UnsignedIntVector indices;
} Mesh;

Mesh chunk_genmesh(Chunk chunk);
void mesh_free(Mesh mesh);
