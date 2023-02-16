#include "../include/textureManager.h"
#include "../include/logger.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

SDL_Texture *textureManager::loadTexture(const char *texture,
                                         SDL_Renderer *render) {

  SDL_Surface *tempSurface = IMG_Load(texture);
  if (tempSurface == NULL) {
    ZeldaError("Could not load texture!", SDL_GetError());
  }
  SDL_Texture *tex = SDL_CreateTextureFromSurface(render, tempSurface);
  SDL_FreeSurface(tempSurface);

  return tex;
}
