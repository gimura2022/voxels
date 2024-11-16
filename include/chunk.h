#define CSIZE 32
#define CQSIZE CSIZE * CSIZE * CSIZE

#define Vectorize(type, name) typedef struct {\
  type *data;\
  unsigned int capacity;\
  unsigned int size;\
  unsigned int step;\
} name;\
name name##_init(unsigned int capacity, unsigned int step);\
void name##_append(name *vec, type value);

#ifdef _chunk_impl
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
#endif // _chunk_impl

Vectorize(float, FloatVector)
Vectorize(unsigned int, UnsignedIntVector)

typedef unsigned char *Chunk;

typedef struct {
  FloatVector vertices;
  UnsignedIntVector indices;
} Mesh;

Chunk chunk_init();
void chunk_set(Chunk chunk, unsigned int x, unsigned int y, unsigned int z, char value); // void chunk set x, y and z (крутая рифма)
unsigned char chunk_get(Chunk chunk, unsigned int x, unsigned int y, unsigned int z);
void chunk_worldgen(Chunk chunk);
void chunk_free(Chunk chunk);

Mesh chunk_genmesh(Chunk chunk);
void mesh_free(Mesh mesh);
