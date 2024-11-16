#define _chunk_impl
#include "chunk.h"

#include <math.h>
#include <string.h>

#define CSIZEI (CSIZE + 1)
#define FloatVector_rgb(r, g, b)\
FloatVector_append(&mesh.vertices, 0.0);\
FloatVector_append(&mesh.vertices, 0.9);\
FloatVector_append(&mesh.vertices, 0.0);

#define FloatVector_addVertex(x, y, z)\
FloatVector_append(&mesh.vertices, x);\
FloatVector_append(&mesh.vertices, y);\
FloatVector_append(&mesh.vertices, z);\
FloatVector_rgb(0.0, 0.9, 0.0)

VectorImpl(float, FloatVector)
VectorImpl(unsigned int, UnsignedIntVector)

Chunk chunk_init() {
  Chunk chunk = malloc(CQSIZE * sizeof(char));
  memset(chunk, 0, CQSIZE * sizeof(char));
  return chunk;
}

void chunk_set(Chunk chunk, unsigned int x, unsigned int y, unsigned int z, char value) {
  if (x >= CSIZE || y >= CSIZE || z >= CSIZE) {
    return;
  }
  chunk[x + y * CSIZE + z * CSIZE * CSIZE] = value;
}

unsigned char chunk_get(Chunk chunk, unsigned int x, unsigned int y, unsigned int z) {
  if (x >= CSIZE || y >= CSIZE || z >= CSIZE) {
    return -1;
  }
  return chunk[x + y * CSIZE + z * CSIZE * CSIZE];
}

Mesh chunk_genmesh(Chunk chunk) {
  Mesh mesh;
  mesh.vertices = FloatVector_init(0, 64);
  mesh.indices = UnsignedIntVector_init(0, 64);

  // I want to create an array of air voxels intersect solid voxels
  // One byte in this array is: 0 0 X+ X- Y+ Y- Z+ Z-
  // where X Y Z are coordinates and + - are representing inc and dec
  unsigned char array[CQSIZE];
  memset(array, 0, CQSIZE);
  for (int x = 0; x < CSIZE; x++) {
    for (int y = 0; y < CSIZE; y++) {
      for (int z = 0; z < CSIZE; z++) {
        char curr = chunk_get(chunk, x, y, z);
        if (curr != 0) {
          unsigned char result = 0;
          char Xinc = chunk_get(chunk, x+1, y, z);
          if (Xinc == 0 || Xinc == -1) {
            result = 0b00100000 | result;
          }
          char Xdec = chunk_get(chunk, x-1, y, z);
          if (Xdec == 0 || Xdec == -1) {
            result = 0b00010000 | result;
          }
          char Yinc = chunk_get(chunk, x, y+1, z);
          if (Yinc == 0 || Yinc == -1) {
            result = 0b00001000 | result;
          }
          char Ydec = chunk_get(chunk, x, y-1, z);
          if (Ydec == 0 || Ydec == -1) {
            result = 0b00000100 | result;
          }
          char Zinc = chunk_get(chunk, x, y, z+1);
          if (Zinc == 0 || Zinc == -1) {
            result = 0b00000010 | result;
          }
          char Zdec = chunk_get(chunk, x, y, z-1);
          if (Zdec == 0 || Zdec == -1) {
            result = 0b00000001 | result;
          }
          array[x + y * CSIZE + z * CSIZE * CSIZE] = result;
        }
      }
    }
  }

  for (int x = 0; x < CSIZE; x++) {
    for (int y = 0; y < CSIZE; y++) {
      for (int z = 0; z < CSIZE; z++) {
        char curr = array[x + y * CSIZE + z * CSIZE * CSIZE];
        if (curr) {
          if ((curr & 0b00100000)) {
            unsigned int size = mesh.vertices.size;
            FloatVector_addVertex(1.0 + x, 0.0 + y, 0.0 + z);
            FloatVector_addVertex(1.0 + x, 1.0 + y, 0.0 + z);
            FloatVector_addVertex(1.0 + x, 0.0 + y, 1.0 + z);
            FloatVector_addVertex(1.0 + x, 1.0 + y, 1.0 + z);

            UnsignedIntVector_append(&mesh.indices, size / 6 + 0);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 3);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
          }
          if ((curr & 0b00010000)) {
            unsigned int size = mesh.vertices.size;
            FloatVector_addVertex(x, 0.0 + y, 0.0 + z);
            FloatVector_addVertex(x, 1.0 + y, 0.0 + z);
            FloatVector_addVertex(x, 0.0 + y, 1.0 + z);
            FloatVector_addVertex(x, 1.0 + y, 1.0 + z);

            UnsignedIntVector_append(&mesh.indices, size / 6 + 0);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 3);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
          }
          if ((curr & 0b00001000)) {
            unsigned int size = mesh.vertices.size;
            FloatVector_addVertex(0.0 + x, 1.0 + y, 0.0 + z);
            FloatVector_addVertex(1.0 + x, 1.0 + y, 0.0 + z);
            FloatVector_addVertex(0.0 + x, 1.0 + y, 1.0 + z);
            FloatVector_addVertex(1.0 + x, 1.0 + y, 1.0 + z);

            UnsignedIntVector_append(&mesh.indices, size / 6 + 0);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 3);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
          }
          if ((curr & 0b00000100)) {
            unsigned int size = mesh.vertices.size;
            FloatVector_addVertex(0.0 + x, y, 0.0 + z);
            FloatVector_addVertex(1.0 + x, y, 0.0 + z);
            FloatVector_addVertex(0.0 + x, y, 1.0 + z);
            FloatVector_addVertex(1.0 + x, y, 1.0 + z);

            UnsignedIntVector_append(&mesh.indices, size / 6 + 0);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 3);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
          }
          if ((curr & 0b00000010)) {
            unsigned int size = mesh.vertices.size;
            FloatVector_addVertex(0.0 + x, 0.0 + y, 1.0 + z);
            FloatVector_addVertex(0.0 + x, 1.0 + y, 1.0 + z);
            FloatVector_addVertex(1.0 + x, 0.0 + y, 1.0 + z);
            FloatVector_addVertex(1.0 + x, 1.0 + y, 1.0 + z);

            UnsignedIntVector_append(&mesh.indices, size / 6 + 0);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 3);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
          }
          if ((curr & 0b00000001)) {
            unsigned int size = mesh.vertices.size;
            FloatVector_addVertex(0.0 + x, 0.0 + y, z);
            FloatVector_addVertex(0.0 + x, 1.0 + y, z);
            FloatVector_addVertex(1.0 + x, 0.0 + y, z);
            FloatVector_addVertex(1.0 + x, 1.0 + y, z);

            UnsignedIntVector_append(&mesh.indices, size / 6 + 0);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 3);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 1);
            UnsignedIntVector_append(&mesh.indices, size / 6 + 2);
          }
        }
      }
    }
  }

  return mesh;
}

void chunk_worldgen(Chunk chunk) {
  for (int x = 0; x < CSIZE; x++) {
    for (int z = 0; z < CSIZE; z++) {
      chunk_set(chunk, x, 0, z, 1);
    }
  }
}

void chunk_free(Chunk chunk) {
  free(chunk);
}

void mesh_free(Mesh mesh) {
  free(mesh.vertices.data);
  free(mesh.indices.data);
}
