#include <GLFW/glfw3.h>

#include <math.h>
#include <stdbool.h>

#include "player.h"

void player_move(Player *player, bool keys[1024], Vec3 dir, float dt) {
	int forward = keys[GLFW_KEY_W] - keys[GLFW_KEY_S];
	int left = keys[GLFW_KEY_A] - keys[GLFW_KEY_D];
	int up = keys[GLFW_KEY_SPACE] - keys[GLFW_KEY_LEFT_SHIFT];

	player->position.z +=
		(forward * cos(dir.x) - left * sin(dir.x)) * player->speed * dt;
	player->position.x +=
		(left * cos(dir.x) + forward * sin(dir.x)) * player->speed * dt;
	player->position.y += up * player->speed * dt;
}
