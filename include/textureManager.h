#include "zeldaEng.h"

#ifndef textureManager_h_
#define textureManager_h_

class textureManager {
public:
  static SDL_Texture *loadTexture(const char *texture);
  static void DrawTexture(SDL_Texture *texture, SDL_Rect source, SDL_Rect dest);
  static void setBackground(const char *texture);
};

#endif
