#include "../box2d/box2d.h"
#include "ecs.h"
#include <glm/glm.hpp>

class BoxCollider2DComponent : public Component {
public:
  glm::vec2 Offset = {0.0f, 0.0f};
  glm::vec2 Size = {0.0f, 0.0f};

  float Density = 1.0f;
  float Friction = 0.5f;
  float Restitution = 0.0f;
  float RestitutionThreshold = 0.5f;

  // storage for runtime
  void *RuntimeFixture = nullptr;

  BoxCollider2DComponent() = default;
  BoxCollider2DComponent(const BoxCollider2DComponent &) = default;
};
