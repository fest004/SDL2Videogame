#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../textureManager.h"
#include "positionComponent.h"
#include <SDL2/SDL.h>

class spriteComponent : public Component {
public:
  spriteComponent() = default;
  spriteComponent(const char *path) {
    texture = textureManager::loadTexture(path);
  }

  void init() override {
    position = &entity->getComponent<PositionComponent>();

    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = 32;
    sourceRectangle.h = 32;

    destinationRect.w = 32;
    destinationRect.h = 32;
  }

  void update() override {
    destinationRect.x = position->GetX();
    destinationRect.y = position->GetY();
  }

  void draw() override {
    textureManager::DrawTexture(texture, sourceRectangle, destinationRect);
  }

private:
  PositionComponent *position;
  SDL_Texture *texture;
  SDL_Rect sourceRectangle, destinationRect;
};

#endif
