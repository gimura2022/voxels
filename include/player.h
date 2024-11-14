#include "window.h"

typedef struct {
  float x, y, z;
} Vec3;

typedef struct {
  Vec3 position;
  Vec3 velocity;
  Vec3 acceleration;
  float speed;
} Player;

void player_move(Window* window, Player *player);
