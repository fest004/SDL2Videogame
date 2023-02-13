#include "ZeldaEng.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

ZeldaEng::ZeldaEng(){};
ZeldaEng::~ZeldaEng(){};

void ZeldaEng::Init(const char *title, int xpos, int ypos, int width,
                    int height, bool fullscreen) {
  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    LOG("SDL Initiliazed");

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
      LOG("Window created");
    } else {
      printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      LOG("Renderer created");
    } else {
      printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
    }
    isRunning = true;
  } else {
    isRunning = false;
  }
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

void ZeldaEng::Update() {}

void ZeldaEng::Render() {
  SDL_RenderClear(renderer);
  // Add stuff to render
  SDL_RenderPresent(renderer);
}

void ZeldaEng::Clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  LOG("Instance cleaned");
}