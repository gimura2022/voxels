#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include "../include/window.h"
#include "../include/shader.h"
#include "../include/logs.h"

#define M_PI 3.14159265358979323846

GLfloat vertices[] = {
   0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // Верхний правый угол
   0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Нижний правый угол
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Нижний левый угол
  -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // Верхний левый угол
};

GLuint indices[] = {
  0, 1, 2,
  2, 3, 0,
};

void print_mat4(mat4 mat) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) printf("%f ", mat[i][j]);
    printf("\n");
  }
}

int main() {
  Window window = createWindow(800, 600);
  if(initWindow(&window) != 0) {
    error("Окно не было инициализировано ,_,");
    glfwTerminate();
    return -1;
  }
  info("Окно было инициализировано");

  GLuint vertex_shader = compile_shader("shaders/default.vert", GL_VERTEX_SHADER);
  if (!vertex_shader) {
    glfwTerminate();
    return -1;
  }

  GLuint fragment_shader = compile_shader("shaders/default.frag", GL_FRAGMENT_SHADER);
  if (!fragment_shader) {
    glfwTerminate();
    return -1;
  }

  GLuint shader_program = compile_shader_program(vertex_shader, fragment_shader);
  if (!shader_program) {
    glfwTerminate();
    return -1;
  }

  // После линкинга в шейдерной программе они больше не нужны
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  // WARNING: A DUNGER STARTS!

  GLuint VAO;  // Vertex Attribute Object(?)
  glGenVertexArrays(1, &VAO);

  GLuint VBO;  // Vertex Buffer Object
  glGenBuffers(1, &VBO);

  GLuint EBO;  // Element (Index) Buffer Object
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  // WARNING: THE DUNGER ENDS!

  glViewport(0, 0, window.width, window.height);

  info("Программа была полностью инициализирована. Запущен игровой цикл");

  // float player_pos[3] = {0.0f, 0.0f, 5.0f};
  // float player_speed = 0.1f;
  double xpos, ypos = 0.1f;

  while (!windowShouldClose(&window)) {
    glfwPollEvents();

    int width = window.width;
    int height = window.height;
    getCursorPos(&window, &xpos, &ypos);

    double xnpos = xpos / width  * M_PI - M_PI / 2.0f;
    double ynpos = ypos / height * M_PI - M_PI / 2.0f;
    xnpos *= (double)width / height;

    // if (wasd & 0b0001) {
    //   player_pos[2] += -player_speed;
    // }
    // if (wasd & 0b0010) {
    //   player_pos[2] += player_speed;
    // }
    // if (wasd & 0b0100) {
    //   player_pos[0] += -player_speed;
    // }
    // if (wasd & 0b1000) {
    //   player_pos[0] += player_speed;
    // }
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4 projection;
    glm_perspective_default((float)width/(float)height, projection);
    GLint projection_location = glGetUniformLocation(shader_program, "projection");

    vec4 translation = {0.0f, 0.0f, -1.0f, 0.0f};
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, translation);
    GLint model_location = glGetUniformLocation(shader_program, "model");

    mat4 view;
    glm_mat4_identity(view);
    // vec3 vec = {1.0, 0.0, 0.0};
    // glm_rotate(view, ynpos, vec);
    // vec3 vec2 = {0.0, 1.0, 0.0};
    // glm_rotate(view, xnpos, vec2);
    vec3 vec = {ynpos, xnpos, 0.0};
    glm_rotate(view, sqrt(xnpos * xnpos + ynpos * ynpos), vec);
    GLint view_location = glGetUniformLocation(shader_program, "view");

    glUseProgram(shader_program);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection[0]);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, view[0]);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, model[0]);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // With EBO

    glBindVertexArray(0);

    swapBuffer(&window);
  }
  glfwTerminate();
  info("Программа завершена");

  return 0;
}

// TODO: a Player struct
// TODO: Player movement
// TODO: a Camera struct
// TODO: fix camera rotation
// TODO: render a single cube
// TODO: render a chunk of cubes
// TODO: create a mesh for every chunk
// TODO: a system of loading-unloading chunks depending on the distance from the player
// TODO: world generation
