#include <SDL2/SDL.h>

class ColliderComponent;

class Collision {
public:
  // Axis Align Bounding Box
  static bool AABB(const SDL_Rect &rectangle1, const SDL_Rect &rectangle2);
  static bool AABB(const ColliderComponent &collider1,
                   const ColliderComponent &collider2);
};
