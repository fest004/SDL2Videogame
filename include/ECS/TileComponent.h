#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "ecs.h"
#include <SDL2/SDL.h>

class TileComponent : public Component {
public:
  TransformComponent *transform;
  SpriteComponent *sprite;

  SDL_Rect tileRectangle;
  int tileID;
  const char *path;

  TileComponent() = default;

  TileComponent(int x, int y, int w, int h, int ID) {
    tileRectangle.x = x;
    tileRectangle.y = y;
    tileRectangle.w = w;
    tileRectangle.h = h;
    tileID = ID;

    switch (tileID) {
    case 0:
      path = "../assets/Tilemaps/CityTilemap/Tiles/"
             "IndustrialTile_05.png";
      break;
    case 1:
      path = "assets/Tilemaps/CityTilemap/Tiles/"
             "IndustrialTile_18.png";
    default:
      path = "../assets/Tilemaps/CityTilemap/Tiles/"
             "IndustrialTile_18.png";
    }
  }

  void init() override {
    entity->addComponent<TransformComponent>(
        (float)tileRectangle.x, (float)tileRectangle.y, (float)tileRectangle.w,
        (float)tileRectangle.h, 1);
    transform = &entity->getComponent<TransformComponent>();

    entity->addComponent<SpriteComponent>(path);
    sprite = &entity->getComponent<SpriteComponent>();
  }
};

#endif
