#include "logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

class Countdown {
public:
  Countdown(int cooldown) {
    // Gets how long SDL has been running
    // and takes in argument that decided how
    // long the countdown lost
    startTime = SDL_GetTicks64();
    currentTime = startTime;
    elapsedTime = 0;
    cooldownTime = cooldown;
  }

  // Every tick updates how much time has went since the clock started

  void tick() {
    currentTime = SDL_GetTicks64();
    elapsedTime = currentTime - startTime;
  }

  // Resets to the same countdown it originally was
  void reset() {
    startTime = SDL_GetTicks64();
    currentTime = startTime;
    elapsedTime = 0;
  }

  // Resets countdown to a new given amount
  void reset(int cooldown) {
    startTime = SDL_GetTicks64();
    currentTime = startTime;
    elapsedTime = 0;
    cooldownTime = cooldown;
  }

  // Checks if time is done
  bool isEnded() { return elapsedTime >= cooldownTime; }

private:
  int cooldownTime;
  Uint64 startTime;
  Uint64 currentTime;
  Uint64 elapsedTime;
};
