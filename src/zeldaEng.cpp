#include "../include/box2d/box2d.h"
#include "../include/core.h"
#include "MyContactListener.cpp"
#include "Vector2D.cpp"
#include "collision.cpp"
#include "ecs.cpp"
#include "gameObject.cpp"
#include "globals.cpp"
#include "textureManager.cpp"
#include "tilemap.cpp"
#include <thread>

tilemap *map;

b2World boxworld({0.0f, 9.8f});

ZeldaEng::ZeldaEng(){};
ZeldaEng::~ZeldaEng(){};

// Timer timer;

SDL_Event ZeldaEng::event;

SDL_Renderer *ZeldaEng::renderer = nullptr;

std::vector<std::unique_ptr<ColliderComponent>> ZeldaEng::colliders;

Manager manager;
auto &Player(manager.addEntity());

enum groupLabel : std::size_t {
  groupMap,
  groupPlayers,
  groupEnemies,
  groupColliders
};

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

  initBox();
  contactListener = *new MyContactListener();
  boxworld.SetContactListener(&contactListener);

  map = new tilemap();

  tilemap::LoadTilemap("../assets/TestMap3232Nr2.txt", 32, 32);

  delete map;

  Player.addComponent<RigidBody2DComponent>(true, 200, 200);
  Player.addComponent<BoxCollider2DComponent>("player");

  Player.addComponent<SpriteComponent>(
      "../assets/spritesheets/zeldaleftTest.png");

  Player.addGroup(groupPlayers);
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

  glm::float32 timeStep = 1.0f / 60.0f; // time step of 1/60th of a second
  boxworld.Step(timeStep, 6, 2);
}

void ZeldaEng::FixedUpdate() {}

auto &tiles(manager.getGroup(groupMap));
auto &players(manager.getGroup(groupPlayers));
auto &enemies(manager.getGroup(groupEnemies));

void ZeldaEng::Render() {
  SDL_RenderClear(renderer);
  // Add stuff to render
  textureManager::setBackground(
      "../assets/backgrounds/CityBackground/city 1/10.png");

  for (auto &t : tiles) {
    t->draw();

    if (t->hasComponent<BoxCollider2DComponent>()) {
      t->getComponent<BoxCollider2DComponent>().DrawOutline(renderer);
    }
  }
  for (auto p : players) {
    p->draw();

    p->getComponent<BoxCollider2DComponent>().DrawOutline(renderer);
  }
  for (auto e : enemies) {
    e->draw();
  }

  SDL_RenderPresent(renderer);
}

void ZeldaEng::Clean() {
  ZeldaCritical("ZeldaEngine Closed");
  LogManager.Shutdown();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void ZeldaEng::AddTile(int ID, int x, int y) {
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(x, y, 32, 32, ID);
  tile.addGroup(groupMap);
}
