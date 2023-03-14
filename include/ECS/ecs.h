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
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
  static ComponentID lastID = 0u;
  return lastID++;
}

template <typename Type> inline ComponentID getComponentTypeID() noexcept {
  static_assert(std::is_base_of<Component, Type>::value, "");
  static ComponentID typeID = getNewComponentTypeID();
  // static ComponentID typeID{getComponentTypeID()};
  return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

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
  Entity(Manager &mManager) : manager(mManager) {}

  void update() {
    for (auto &component : components)
      component->update();
  }
  void draw() {
    for (auto &component : components)
      component->draw();
  }
  bool isActive() const { return active; }
  void destroy() { active = false; }

  bool hasGroup(Group mGroup) { return groupBitSet[mGroup]; }

  void addGroup(Group mGroup);
  void deleteGroup(Group mGroup) { groupBitSet[mGroup] = false; }

  template <typename type> bool hasComponent() const {
    return componentBitSet[getComponentTypeID<type>()];
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
  Manager &manager;
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitSet;
  GroupBitSet groupBitSet;
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
    for (auto i(0u); i < maxGroups; i++) {
      auto &v(groupedEntities[i]);
      v.erase(std::remove_if(std::begin(v), std::end(v),
                             [i](Entity *mEntity) {
                               return !mEntity->isActive() ||
                                      !mEntity->hasGroup(i);
                             }),
              std::end(v));
    }

    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity> &mEntity) {
                                    return !mEntity->isActive();
                                  }),
                   std::end(entities));
  }

  void AddToGroup(Entity *mEntity, Group mGroup) {
    groupedEntities[mGroup].emplace_back(mEntity);
  }

  std::vector<Entity *> &getGroup(Group mGroup) {
    return groupedEntities[mGroup];
  }

  Entity &addEntity() {
    Entity *newEntity = new Entity(*this);
    std::unique_ptr<Entity> uniquepointer{newEntity};
    entities.emplace_back(std::move(uniquepointer));
    return *newEntity;
  }

private:
  std::array<std::vector<Entity *>, maxGroups> groupedEntities;
  std::vector<std::unique_ptr<Entity>> entities;
};

#endif
