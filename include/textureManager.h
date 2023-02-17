#ifndef textureManager_h_
#define textureManager_h_

#include "zeldaEng.h"

class textureManager {
public:
  static SDL_Texture *loadTexture(const char *texture);
};

#endif
