#include "../include/core.h"

ZeldaEng *engine = nullptr;

int main(int argc, const char *argv[]) {
  engine = new ZeldaEng();
  engine->Init("Zelda", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024,
               1024, false);

  // Countdown countdown;
  // countdown.reset(20);

  while (engine->Running()) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    // countdown.tick();

    engine->EventHandle();
    engine->Update();
    engine->Render();

    // if (countdown.isEnded()) {
    //   engine->FixedUpdate();
    //   countdown.reset();
    // }
  }

  engine->Clean();
  delete engine;
  return 0;
}
