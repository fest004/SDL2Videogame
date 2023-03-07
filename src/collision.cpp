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

bool Collision::AABB(const ColliderComponent &collider1,
                     const ColliderComponent &collider2) {

  // if (AABB(collider1.collider, collider2.collider) && collider2.tag !=
  // "player") {
  if (AABB(collider1.collider, collider2.collider)) {
    ZeldaInfo(collider1.tag + " and " + collider2.tag + " collided! ");
    return true;
  }
  return false;
}
