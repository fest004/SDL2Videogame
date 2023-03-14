#include "../include/ECS/ecs.h"

void Entity::addGroup(Group mGroup) {
  groupBitSet[mGroup] = true;
  manager.AddToGroup(this, mGroup);
}
