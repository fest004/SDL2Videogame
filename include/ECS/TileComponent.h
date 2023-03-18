#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "../globals.h"
#include "BoxCollider2DComponent.h"
#include "Rigidbody2DComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "ecs.h"
#include <SDL2/SDL.h>

class TileComponent : public Component {
public:
  RigidBody2DComponent *rigidbody;
  SpriteComponent *sprite;
  BoxCollider2DComponent *colliderComponent;
  std::string tempTag;

  bool isCollider = false;

  SDL_Rect tileRectangle;
  int tileID;
  const char *path;

  TileComponent() = default;
  ~TileComponent() {}

  TileComponent(int x, int y, int w, int h, int ID) {
    tileRectangle.x = x;
    tileRectangle.y = y;
    tileRectangle.w = w;
    tileRectangle.h = h;
    tileID = ID;

    switch (tileID) {
    case 0:
      path = "../assets/DefaultPng.png";
      break;
    case 1:
      // Ground
      path = "../assets/Tilemaps/CityTilemap/Tiles/IndustrialTile_05.png";
      tempTag = "ground";
      isCollider = true;
      break;
    case 2:
      // Box
      path = "../assets/Tilemaps/CityTilemap/Tiles/IndustrialTile_02.png";
      break;
    case 3:
      // FloatingPlatform
      path = "../assets/Tilemaps/CityTilemap/Tiles/IndustrialTile_18.png";
      break;
    case 4:
      // Box 2
      path = "../assets/Tilemaps/CityTilemap/Tiles/IndustrialTile_71.png";
      break;
    case 5:
      // Button looking tile
      path = "../assets/Tilemaps/CityTilemap/Tiles/IndustrialTile_45.png";
      break;
    default:
      path = "../assets/Tilemaps/CityTilemap/Tiles/IndustrialTile_68.png";
      break;
    }
  }

  void init() override {
    entity->addComponent<RigidBody2DComponent>(false, tileRectangle.x,
                                               tileRectangle.y);
    rigidbody = &entity->getComponent<RigidBody2DComponent>();
    int x = rigidbody->GetX();
    int y = rigidbody->GetY();
    // std::cout << "(" << x << ", " << y << ")" << std::endl;

    entity->addComponent<SpriteComponent>(path);
    sprite = &entity->getComponent<SpriteComponent>();

    if (isCollider) {
      entity->addComponent<BoxCollider2DComponent>(tempTag);
      // colliderComponent = &entity->getComponent<BoxCollider2DComponent>();
    }
  }
};

#endif
