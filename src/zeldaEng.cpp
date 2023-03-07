#include "../include/core.h"
#include "Vector2D.cpp"
#include "collision.cpp"
#include "gameObject.cpp"
#include "textureManager.cpp"
#include "tilemap.cpp"
#include <thread>

tilemap *map;

ZeldaEng::ZeldaEng(){};
ZeldaEng::~ZeldaEng(){};

Timer timer;

SDL_Event ZeldaEng::event;

SDL_Renderer *ZeldaEng::renderer = nullptr;

std::vector<ColliderComponent *> ZeldaEng::colliders;

Manager manager;
auto &Player(manager.addEntity());
auto &wall(manager.addEntity());

auto &tile0(manager.addEntity());
auto &tile1(manager.addEntity());

void ZeldaEng::Init(const char *title, int xpos, int ypos, int width,
                    int height, bool fullscreen) {

  LogManager.Init();
  ZeldaTrace("ZeldaEngine V{}.{}", 0, 1);

  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
      ZeldaInfo("Window created");
    } else {
      ZeldaError("Window could not be created. SDL Error:", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      ZeldaInfo("Renderer Created");
    } else {
      ZeldaError("Renderer could not be created! SDL Error:", SDL_GetError());
    }
    isRunning = true;
  } else {
    isRunning = false;
  }
  map = new tilemap();

  tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
  tile0.addComponent<ColliderComponent>("ground");

  tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
  tile1.addComponent<ColliderComponent>("platform");

  Player.addComponent<TransformComponent>(0, 200);
  Player.addComponent<SpriteComponent>(
      "../assets/spritesheets/zeldaleftTest.png");
  Player.addComponent<KeyboardController>();
  Player.addComponent<ColliderComponent>("player");

  wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
  wall.addComponent<SpriteComponent>(
      "../assets/spritesheets/zeldaleftTest.png");
  wall.addComponent<ColliderComponent>("wall");
}

void ZeldaEng::EventHandle() {
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  }
}

void ZeldaEng::Update() {
  manager.refresh();
  manager.update();

  for (ColliderComponent *collider_component : colliders) {
    if (collider_component->tag != "player") {
      Collision::AABB(Player.getComponent<ColliderComponent>(),
                      *collider_component);
    }
  }

  // Collision logic, to be moved
  //
}

void ZeldaEng::FixedUpdate() {}

void ZeldaEng::Render() {
  SDL_RenderClear(renderer);
  // Add stuff to render
  textureManager::setBackground(
      "../assets/backgrounds/CityBackground/city 1/10.png");

  map->DrawTileMap();
  tile0.draw();
  tile1.draw();
  Player.draw();
  wall.draw();
  SDL_RenderPresent(renderer);
}

void ZeldaEng::Clean() {
  ZeldaCritical("ZeldaEngine Closed");
  LogManager.Shutdown();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
