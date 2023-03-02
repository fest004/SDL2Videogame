#ifndef TIMER_H
#define TIMER_H

#include "SDL2/SDL.h"

class Timer {
public:
  Timer() {
    startTime = SDL_GetTicks64();
    currentTime = startTime;
    elapsedTime = 0;
  }

  void tick() {
    currentTime = SDL_GetTicks64();
    elapsedTime = currentTime - startTime;
  }

  Uint64 getElapsedTime() { return elapsedTime; }

private:
  Uint64 startTime;
  Uint64 currentTime;
  Uint64 elapsedTime;
};

#endif
