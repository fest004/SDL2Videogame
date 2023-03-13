#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../textureManager.h"
#include "TransformComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

class SpriteComponent : public Component {
public:
  SpriteComponent() = default;

  SpriteComponent(const char *path) {
    texture = textureManager::loadTexture(path);
  }
  ~SpriteComponent() { SDL_DestroyTexture(texture); }

  void setTexture(const char *path) {

    texture = textureManager::loadTexture(path);
  }

  void init() override {
    transform = &entity->getComponent<TransformComponent>();

    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = transform->width;
    sourceRectangle.h = transform->height;
  }

  void update() override {
    destinationRect.x = static_cast<int>(transform->position.x);
    destinationRect.y = static_cast<int>(transform->position.y);
    destinationRect.w = transform->width * transform->scale;
    destinationRect.h = transform->height * transform->scale;
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
