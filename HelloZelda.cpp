#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string>

enum KeyPressButton {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

int WINDOW_HEIGHT = 480;
int WINDOW_WIDTH = 720;

// Starts up SDL and creates window
bool init();

// Loads media like images and audio
bool loadMedia();

// Frees media and closes SDL
void close();

// Window we are rendering to
SDL_Window *gWindow = NULL;

// Surface cointained by the window
SDL_Surface *gScreenSurface = NULL;

// The surface we will load and show on the screen
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *gCurrentSurface = NULL;

SDL_Surface *loadSurface(std::string path);

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize!\n");
    close();
  }

  if (!loadMedia()) {
    printf("Failed to load media!\n");
    close();
  }
  bool quit = false;
  SDL_Event e;

  while (!quit) {
    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {

        switch (e.key.keysym.sym) {
        case SDLK_UP:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
          break;

        case SDLK_DOWN:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
          break;

        case SDLK_LEFT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
          break;

        case SDLK_RIGHT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
          break;

        default:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
          break;
        }
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = WINDOW_WIDTH;
        stretchRect.h = WINDOW_HEIGHT;
        SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  close();
  return 0;
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *optimizedSurface = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
  } else {

    optimizedSurface =
        SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

bool init() {
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("Zelda", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                               WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("SDL could not create window! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Get window surface!!!
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia() {
  bool success = true;

  // Load default image
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
      SDL_LoadBMP("Assets/Sprites/press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("SDL could not load default image! SDL ERROR: %s\n", SDL_GetError());
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] =
      SDL_LoadBMP("Assets/Sprites/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Could not load 'UP' image! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] =
      SDL_LoadBMP("Assets/Sprites/down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Could not load 'Down' image! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] =
      SDL_LoadBMP("Assets/Sprites/left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Could not load 'LEFT' image! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] =
      SDL_LoadBMP("Assets/Sprites/right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Could not load 'RIGHT' image! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  return success;
}

void close() {
  // Deallocate surfcae
  SDL_FreeSurface(gCurrentSurface);
  gCurrentSurface = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}
