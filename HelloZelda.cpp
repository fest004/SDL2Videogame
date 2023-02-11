#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
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

// Creates a rectangle and renders to screen
bool CreateRect();

// Frees media and closes SDL
void close();

// Loads individual image as texture
SDL_Texture *loadTexture(std::string path);

// Current displayed texture
SDL_Texture *gTexture = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Window we are rendering to
SDL_Window *gWindow = NULL;

// Surface cointained by the window
SDL_Surface *gScreenSurface = NULL;

// The surface we will load and show on the screen
SDL_Texture *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

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
    gTexture = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {

        switch (e.key.keysym.sym) {
        case SDLK_UP:
          gTexture = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
          break;

        case SDLK_DOWN:
          gTexture = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
          break;

        case SDLK_LEFT:
          gTexture = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
          break;

        case SDLK_RIGHT:
          gTexture = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
          break;

        case SDLK_v:
          gTexture = NULL;
          CreateRect();
          printf("Create rect");
          break;

        default:
          gTexture = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
          break;
        }
        if (gTexture != NULL) {
          SDL_Rect stretchRect;
          stretchRect.x = 0;
          stretchRect.y = 0;
          stretchRect.w = WINDOW_WIDTH;
          stretchRect.h = WINDOW_HEIGHT;
        }

        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}

SDL_Texture *loadTexture(std::string path) {
  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
  } else {

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return newTexture;
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
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (gRenderer == NULL) {
        printf("Your renderer could not be created! %s\n", SDL_GetError());
        success = false;
      } else {
        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        } else {
          gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
      }
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;

  // Load default image
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
      loadTexture("Assets/Sprites/press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("SDL could not load default image! SDL ERROR: %s\n", SDL_GetError());
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] =
      loadTexture("Assets/Sprites/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Could not load 'UP' image! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] =
      loadTexture("Assets/Sprites/down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Could not load 'Down' image! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] =
      loadTexture("Assets/Sprites/left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Could not load 'LEFT' image! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] =
      loadTexture("Assets/Sprites/right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Could not load 'RIGHT' image! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  return success;
}

bool CreateRect() {
  bool success = true;
  SDL_Rect fillRect = {WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_HEIGHT / 2,
                       WINDOW_WIDTH / 2};
  SDL_SetRenderDrawColor(gRenderer, 10, 10, 10, 0xFF);
  SDL_RenderFillRect(gRenderer, &fillRect);
  return success;
}

void close() {
  // Deallocate surfcae
  SDL_DestroyTexture(gTexture);
  gTexture = NULL;

  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gRenderer = NULL;
  gWindow = NULL;

  SDL_Quit();
}
