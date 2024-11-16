#include "chunk.h"
#include "utils.h"

#ifndef _mesh
#define _mesh
typedef struct {
	FloatVector vertices;
	UnsignedIntVector indices;
} Mesh;

Mesh chunk_genmesh(Chunk chunk);
void mesh_free(Mesh mesh);
#endif // _mesh
