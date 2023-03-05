#include <SDL2/SDL.h>

class Collision {
public:
  // Impleneted in src/Collision.cpp
  //  Axis Align Bounding Box
  static bool AABB(const SDL_Rect &rectangle1, const SDL_Rect &rectangle2);
};
