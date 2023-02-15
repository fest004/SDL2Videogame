#include "../include/zeldaEng.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

ZeldaEng *engine = nullptr;

int main(int argc, const char *argv[]) {
  engine = new ZeldaEng();
  engine->Init("Zelda", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,
               600, false);

  while (engine->Running()) {
    engine->EventHandle();
    engine->Update();
    engine->Render();
  }

  engine->Clean();
  return 0;
}
