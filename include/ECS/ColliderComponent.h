#include "../zeldaEng.h"
#include "SDL2/SDL.h"
#include "TransformComponent.h"
#include <string>

class ColliderComponent : public Component {
public:
  SDL_Rect collider;
  std::string tag;

  TransformComponent *transform;

  ColliderComponent(std::string t) { tag = t; }

  void init() override {
    if (!entity->hasComponent<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    std::cout << this->tag << std::endl;

    ZeldaEng::colliders.push_back(this);
  }

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
