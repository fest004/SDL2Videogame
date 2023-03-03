#include "../include/ECS/Collision.h"
#include "../include/core.h"

bool Collision::AABB(const SDL_Rect &rectangle1, const SDL_Rect &rectangle2) {
  if (rectangle1.x + rectangle1.w >= rectangle2.x &&
      rectangle2.x + rectangle2.w >= rectangle1.x &&
      rectangle1.y + rectangle1.h >= rectangle2.y &&
      rectangle2.y + rectangle2.h >= rectangle1.y) {
    return true;
  }
  return false;
}
