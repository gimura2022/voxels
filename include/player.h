#include "utils.h"

#ifndef _player
#define _player
typedef struct {
  Vec3 position;
  Vec3 velocity;
  Vec3 acceleration;
  float speed;
} Player;

void player_move(Player *player, bool keys[1024], Vec3 cameraDirection, float dt);
#endif // _player
