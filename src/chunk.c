#include "chunk.h"

#include <stdlib.h>
#include <string.h>

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
