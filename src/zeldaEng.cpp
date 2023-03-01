#include "../include/core.h"
#include "Vector2D.cpp"
#include "gameObject.cpp"
#include "textureManager.cpp"
#include "tilemap.cpp"
#include <thread>

tilemap *map;

ZeldaEng::ZeldaEng(){};
ZeldaEng::~ZeldaEng(){};

SDL_Renderer *ZeldaEng::renderer = nullptr;

Manager manager;
auto &Player(manager.addEntity());

void ZeldaEng::Init(const char *title, int xpos, int ypos, int width,
                    int height, bool fullscreen) {

  LogManager.Init();
  ZeldaTrace("ZeldaEngine V{}.{}", 0, 1);

  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    ZeldaInfo("SDL Initiliazed");

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
      // Test errorcolor
      ZeldaInfo("Window created");
    } else {
      ZeldaError("Window could not be created. SDL Error:", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      // Test Warningcolor
      ZeldaInfo("Renderer Created");
    } else {
      ZeldaError("Renderer could not be created! SDL Error:", SDL_GetError());
    }
    isRunning = true;
  } else {
    isRunning = false;
  }
  map = new tilemap();

  Player.addComponent<TransformComponent>(0, 200);
  Player.addComponent<SpriteComponent>(
      "../assets/spritesheets/zeldaleftTest.png");
}

void ZeldaEng::EventHandle() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  }
}

void ZeldaEng::Update() {
  // Player.draw();
  //
  //
  manager.update();
  manager.draw();
  manager.refresh();
  Player.getComponent<TransformComponent>().position.AddVector(Vector2D(5, 0));
  if (Player.getComponent<TransformComponent>().position.x > 20) {
    Player.getComponent<SpriteComponent>().setTexture(
        "../assets/Tilemaps/CityTilemap/Objects/2.png");
  }
}

void ZeldaEng::FixedUpdate() {}

void ZeldaEng::Render() {
  SDL_RenderClear(renderer);
  // Add stuff to render
  textureManager::setBackground(
      "../assets/backgrounds/CityBackground/city 1/10.png");

  map->DrawTileMap();
  Player.draw();
  SDL_RenderPresent(renderer);
}

void ZeldaEng::Clean() {
  ZeldaCritical("ZeldaEngine Closed");
  LogManager.Shutdown();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
