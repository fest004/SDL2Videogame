#include "logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

class Countdown {
public:
  Countdown(int cooldown) {
    startTime = SDL_GetTicks64();
    currentTime = startTime;
    elapsedTime = 0;
    cooldownTime = cooldown;
  }

  void tick() {
    currentTime = SDL_GetTicks64();
    elapsedTime = currentTime - startTime;
  }

  void reset() {
    startTime = SDL_GetTicks64();
    currentTime = startTime;
    elapsedTime = 0;
  }

  void reset(int cooldown) {
    startTime = SDL_GetTicks64();
    currentTime = startTime;
    elapsedTime = 0;
    cooldownTime = cooldown;
  }

  bool isEnded() { return elapsedTime >= cooldownTime; }

private:
  int cooldownTime;
  Uint64 startTime;
  Uint64 currentTime;
  Uint64 elapsedTime;
};
