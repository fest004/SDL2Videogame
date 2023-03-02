#include "log.h"
#include "timestep.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#ifndef zeldaEng_h
#define zeldaEng_h

class ZeldaEng {

public:
  ZeldaEng();
  ~ZeldaEng();

  void Init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  void EventHandle();
  void Update();
  void FixedUpdate();
  void Render();
  void Clean();

  bool Running() { return isRunning; };

  static SDL_Renderer *renderer;
  static SDL_Event event;

private:
  int count;
  bool isRunning;
  SDL_Window *window;

  Log LogManager;
};

#endif
