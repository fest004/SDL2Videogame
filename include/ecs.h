#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

#ifndef ecs_h_
#define ecs_h_

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
  static ComponentID lastID = 0;
  return lastID++;
}

template <typename Type> inline ComponentID getComponentTypeID() noexcept {
  static ComponentID typeID = getComponentTypeID();
  return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component {
public:
  Entity *entity;

  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}

  virtual ~Component() {}
};

class Entity {
public:
  void update() {
    for (auto &component : components)
      component->update();
    for (auto &component : components)
      component->draw();
  }
  void draw() {}
  bool isActive() const { return active; }
  void destroy() { active = false; }

  template <typename type> bool hasComponent() const {
    return componentBitSet[getComponentTypeID<type>];
  }

  template <typename type, typename... TypeArgs>
  type &addComponent(TypeArgs &&...mArgs) {
    type *component(new type(std::forward<TypeArgs>(mArgs)...));
    component->entity = this;
    std::unique_ptr<Component> uniquepointer{component};
    components.emplace_back(std::move(uniquepointer));

    componentArray[getComponentTypeID<type>()] = component;
    componentBitSet[getComponentTypeID<type>()] = true;

    component->init();

    return *component;
  }

  template <typename type> type &getComponent() const {
    auto ptr(componentArray[getComponentTypeID<type>()]);
    return *static_cast<type *>(ptr);
  }
  // gameobject.getComponent<PositionComponent>().setXpos(25);

private:
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitSet;
};

class Manager {
public:
  void update() {
    for (auto &entity : entities)
      entity->update();
  }

  void draw() {
    for (auto &entity : entities)
      entity->draw();
  }

  void refresh() {
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity> &mEntity) {
                                    return !mEntity->isActive();
                                  }),
                   std::end(entities));
  }

  Entity &addEntity() {
    Entity *newEntity = new Entity();
    std::unique_ptr<Entity> uniquepointer{newEntity};
    entities.emplace_back(std::move(uniquepointer));
    return *newEntity;
  }

private:
  std::vector<std::unique_ptr<Entity>> entities;
};

#endif
