#include "../include/core.h"

gameObject::gameObject(const char *texturesheet, int initialX, int initialY) {
  objectTexture = textureManager::loadTexture(texturesheet);
  xpos = initialX;
  ypos = initialY;
}

void gameObject::Update() {
  sourceRectangle.h = 32;
  sourceRectangle.w = 32;
  sourceRectangle.x = 0;
  sourceRectangle.y = 0;

  destinationRectangle.x = xpos;
  destinationRectangle.y = ypos;
  destinationRectangle.w = sourceRectangle.w;
  destinationRectangle.h = sourceRectangle.h;
}

void gameObject::Render() {
  SDL_RenderCopy(ZeldaEng::renderer, objectTexture, &sourceRectangle,
                 &destinationRectangle);
}
