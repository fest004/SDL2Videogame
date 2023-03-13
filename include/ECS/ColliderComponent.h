#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "../zeldaEng.h"
#include "SDL2/SDL.h"
#include "TransformComponent.h"
#include <string>

class ColliderComponent : public Component {
public:
  SDL_Rect collider;

  // A tag to recognise what kind of collider it is
  std::string tag;

  // Setting a position for the component
  TransformComponent *transform;

  ColliderComponent(std::string t) { tag = t; }

  // Sets a transformcomponent to a Collider if not set already
  void init() override {
    if (!entity->hasComponent<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    std::cout << this->tag << std::endl;

    auto collider = std::make_shared<ColliderComponent>(*this);
    ZeldaEng::colliders.push_back(std::unique_ptr<ColliderComponent>(this));
  }

  // Keeping its position updated throughout

  void update() override {
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
  }

  // SDL_Rect GetCollider()
  // {
  //
  // }
};

#endif
