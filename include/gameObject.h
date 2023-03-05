
#include "zeldaEng.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// Create methods for gameObjects, gets implemented in src/gameObject.cpp

class gameObject {
public:
  gameObject(const char *texturesheet, int initialX, int initialY);
  ~gameObject();

  void Update();
  void Render();

private:
  int xpos;
  int ypos;

  SDL_Texture *objectTexture;
  SDL_Rect sourceRectangle, destinationRectangle;
};

#endif
