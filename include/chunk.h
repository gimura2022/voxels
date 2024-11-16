#define CSIZE 32
#define CQSIZE CSIZE *CSIZE *CSIZE

typedef unsigned char *Chunk;

Chunk chunk_init();
void chunk_set(Chunk chunk, unsigned int x, unsigned int y, unsigned int z,
			   char value); // void chunk set x, y and z (крутая рифма)
unsigned char chunk_get(Chunk chunk, unsigned int x, unsigned int y,
						unsigned int z);
void chunk_worldgen(Chunk chunk);
void chunk_free(Chunk chunk);
