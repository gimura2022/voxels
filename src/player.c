#include "../include/player.h"

void player_move(Window* window, Player *player) {
  int forward = glfwGetKey(window->window, GLFW_KEY_W) - glfwGetKey(window->window, GLFW_KEY_S);
  int left = glfwGetKey(window->window, GLFW_KEY_A) - glfwGetKey(window->window, GLFW_KEY_D);
  int up = glfwGetKey(window->window, GLFW_KEY_SPACE) - glfwGetKey(window->window, GLFW_KEY_LEFT_SHIFT);

  player->position.x += left * player->speed;
  player->position.y += up * player->speed;
  player->position.z += forward * player->speed;
}
