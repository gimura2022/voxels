#include "camera.h"
#include "mesh.h"
#include "player.h"

typedef struct {
	bool *polygon_mode;
	unsigned int shader_program;
	unsigned int VAO;
	int *width, *height;
} Renderer;

unsigned int render_create_shader(void);
unsigned int render_create_vao(Mesh mesh, int width, int height);
// void render(unsigned int shader_program, Mesh *mesh, Player *player, Camera
// *camera, unsigned int VAO, bool polygon_mode, int width, int height);
void render(Renderer *renderer, Mesh *mesh, Player *player, Camera *camera);
