#include "log.h"
#include "timestep.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>

class ColliderComponent;

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

  static void AddTile(int ID, int x, int y);

  bool Running() { return isRunning; };

  static SDL_Renderer *renderer;
  static SDL_Event event;
  static std::vector<std::unique_ptr<ColliderComponent>> colliders;

  Log LogManager;

private:
  int count;
  bool isRunning;
  SDL_Window *window;

  // Log LogManager;
};

#endif
