#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include <string.h>

#include "window.h"
#include "shader.h"
#include "logs.h"
#include "player.h"
#include "camera.h"
#include "chunk.h"
#include "mesh.h"

#define M_PI 3.14159265358979323846

void print_mat4(mat4 mat) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) printf("%f ", mat[i][j]);
    printf("\n");
  }
}

GLuint create_shader() {
  GLuint vertex_shader = compile_shader("shaders/default.vert", GL_VERTEX_SHADER);
  if (!vertex_shader) {
    glfwTerminate();
    return 0;
  }

  GLuint fragment_shader = compile_shader("shaders/default.frag", GL_FRAGMENT_SHADER);
  if (!fragment_shader) {
    glfwTerminate();
    return 0;
  }

  GLuint shader_program = compile_shader_program(vertex_shader, fragment_shader);
  if (!shader_program) {
    glfwTerminate();
    return 0;
  }

  // После линкинга в шейдерной программе они больше не нужны
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return shader_program;
}

int main() {
  Window window = createWindow(800, 600);
  if(initWindow(&window) != 0) {
    error("Окно не было инициализировано ,_,");
    glfwTerminate();
    return -1;
  }
  info("Окно было инициализировано");

  Chunk chunk = chunk_init();
  chunk_worldgen(chunk);
  Mesh mesh = chunk_genmesh(chunk);
  FloatVector *vertices = &mesh.vertices;
  UnsignedIntVector *indices = &mesh.indices;

  GLuint shader_program = create_shader();

  // WARNING: A DUNGER STARTS!
  GLuint VAO;  // Vertex Attribute Object(?)
  GLuint VBO;  // Vertex Buffer Object
  GLuint EBO;  // Element (Index) Buffer Object

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices->capacity * sizeof(float), vertices->data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->capacity * sizeof(float), indices->data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
  glBindVertexArray(0);
  // WARNING: THE DUNGER ENDS!

  mesh_free(mesh);
  chunk_free(chunk);

  glViewport(0, 0, window.width, window.height);

  glEnable(GL_DEPTH_TEST);

  Player player = {
    {0.0f, 1.0f, -5.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    3.0f,
  };

  Camera camera = {
    0.0f, 0.0f, 0.0f,
  };

  info("Программа была полностью инициализирована. Запуск игрового цикла...");

  float start = 0.0f;
  float end = 0.0f;
  float dt = 0.0f;
  while (!windowShouldClose(&window)) {
    dt = end - start;
    start = glfwGetTime();
    // LOGIC
    glfwPollEvents();

    int width = window.width;
    int height = window.height;

    camera_update(&camera, window.keys, dt);
    player_move(&player, window.keys, camera.direction, dt);

    // RENDER
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (window.polygon_mode) {
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    mat4 projection;
    glm_perspective_default((float)width/(float)height, projection);
    GLint projection_location = glGetUniformLocation(shader_program, "projection");

    mat4 model;
    vec4 translation = {player.position.x, -player.position.y, player.position.z, 0.0f};
    glm_mat4_identity(model);
    glm_translate(model, translation);
    GLint model_location = glGetUniformLocation(shader_program, "model");

    mat4 view;
    glm_mat4_identity(view);
    vec3 up = {1.0f, 0.0f, 0.0f};
    glm_rotate(view, -camera.direction.y, up);
    vec3 left = {0.0f, 1.0f, 0.0f};
    glm_rotate(view, -camera.direction.x, left);
    GLint view_location = glGetUniformLocation(shader_program, "view");

    glUseProgram(shader_program);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection[0]);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, view[0]);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, model[0]);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mesh.indices.size, GL_UNSIGNED_INT, 0); // With EBO

    glBindVertexArray(0);

    swapBuffer(&window);

    end = glfwGetTime();
  }
  glfwTerminate();
  info("Программа завершена");

  return 0;
}

// TODO: rotate camera using mouse
// TODO: optimize Mesh generating. Сейчас мы генерируем по 4 вершины на каждую грань вокселя. Это 24 вершины на воксель в худшем случае. Но воксель это куб и можно обойтись 8 вершинами
// TODO: add ability to change color of voxel.
// TODO: write a blazingly fast greedy mesher xd lol
// TODO: a system of loading-unloading chunks depending on the distance from the player
// TODO: world generation
// TODO: improve camera rotation (use quaternions O.O)
