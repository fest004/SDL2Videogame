#include "../zeldaEng.h"
#include "TransformComponent.h"
#include "ecs.h"
#include <SDL2/SDL_events.h>

class KeyboardController : public Component {
public:
  TransformComponent *transform;

  void init() override {
    transform = &entity->getComponent<TransformComponent>();
  }

  // Simple switch case to see input, and sets velocity on x and y axis based on
  // WASD
  //
  // To be refactored
  void update() override {
    if (ZeldaEng::event.type == SDL_KEYDOWN) {
      switch (ZeldaEng::event.key.keysym.sym) {
      case SDLK_w:
        transform->velocity.y = -1;
        break;
      case SDLK_s:
        transform->velocity.y = 1;
        break;
      case SDLK_a:
        transform->velocity.x = -1;
        break;
      case SDLK_d:
        transform->velocity.x = 1;
        break;

      default:
        break;
      }
    }

    // Stopping when letting key go

    if (ZeldaEng::event.type == SDL_KEYUP) {
      switch (ZeldaEng::event.key.keysym.sym) {
      case SDLK_w:
        transform->velocity.y = 0;
        break;
      case SDLK_s:
        transform->velocity.y = 0;
        break;
      case SDLK_a:
        transform->velocity.x = 0;
        break;
      case SDLK_d:
        transform->velocity.x = 0;
        break;

      default:
        break;
      }
    }
  }
};
