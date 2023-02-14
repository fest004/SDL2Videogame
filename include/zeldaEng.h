

#ifndef Game_hpp
#define Game_hpp
#include "logger/log.h"
#include <SDL2/SDL.h>
#include <stdio.h>

class ZeldaEng {

public:
  ZeldaEng();
  ~ZeldaEng();

  void Init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  void EventHandle();
  void Update();
  void Render();
  void Clean();

  bool Running() { return isRunning; };

private:
  bool isRunning;
  SDL_Window *window;
  SDL_Renderer *renderer;

  Log LogManager;
};

#endif
