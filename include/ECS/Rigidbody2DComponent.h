#include "../box2d/box2d.h"
#include "../world.h"
#include "ecs.h"
#include <glm/glm.hpp>

class RigidBody2DComponent : public Component {
public:
  RigidBody2DComponent(b2World *world, bool isDynamic, int x, int y) {

    b2BodyDef bodyDef;
    bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
    bodyDef.position.Set((float)x, (float)y);
    body = world->CreateBody(&bodyDef);
  }

  void Test(b2World &world, bool isDynamic, int x, int y) {

    b2BodyDef bodyDef;
    bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
    bodyDef.position.Set((float)x, (float)y);
    body = world.CreateBody(&bodyDef);
  }

private:
  b2Body *body;
};
