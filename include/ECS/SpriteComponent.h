#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../textureManager.h"
#include "TransformComponent.h"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
public:
  SpriteComponent() = default;

  SpriteComponent(const char *path) {
    texture = textureManager::loadTexture(path);
  }

  void setTexture(const char *path) {

    texture = textureManager::loadTexture(path);
  }

  void init() override {
    transform = &entity->getComponent<TransformComponent>();

    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = 32;
    sourceRectangle.h = 32;

    destinationRect.w = 32;
    destinationRect.h = 32;
  }

  void update() override {
    destinationRect.x = (int)transform->position.x;
    destinationRect.y = (int)transform->position.y;
  }

  void draw() override {
    textureManager::DrawTexture(texture, sourceRectangle, destinationRect);
  }

private:
  TransformComponent *transform;
  SDL_Texture *texture;
  SDL_Rect sourceRectangle, destinationRect;
};

#endif
