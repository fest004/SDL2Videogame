#include "../include/core.h"
#include "Vector2D.cpp"
#include "gameObject.cpp"
#include "textureManager.cpp"
#include "tilemap.cpp"
#include <thread>

tilemap *map;

ZeldaEng::ZeldaEng(){};
ZeldaEng::~ZeldaEng(){};

Timer timer;
Countdown countdown(5000);

SDL_Event ZeldaEng::event;

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
  Player.addComponent<KeyboardController>();
}

void ZeldaEng::EventHandle() {
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  }
}

int once = 0;
int twice = 0;

void ZeldaEng::Update() {
  // Player.draw();
  //
  //
  manager.update();
  manager.draw();
  manager.refresh();
  countdown.tick();
  if (countdown.isEnded() && once != 1) {
    ZeldaDebug("Countdown ended");
    countdown.reset(10000);
    twice = 2;
  }
  if (countdown.isEnded() && twice == 2) {
    ZeldaDebug("Countdown ended again");
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
