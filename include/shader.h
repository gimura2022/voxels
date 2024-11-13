#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint compile_shader(const char *path, GLenum shader_type);
GLuint compile_shader_program(GLuint vertex_shader, GLuint fragment_shader);
