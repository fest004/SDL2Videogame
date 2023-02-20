#include "../include/textureManager.h"
#include "../include/logger.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

SDL_Texture *textureManager::loadTexture(const char *texture) {

  SDL_Surface *tempSurface = IMG_Load(texture);
  if (tempSurface == NULL) {
    ZeldaError("Could not load texture!", SDL_GetError());
  }
  SDL_Texture *tex =
      SDL_CreateTextureFromSurface(ZeldaEng::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return tex;
}

void textureManager::DrawTexture(SDL_Texture *texture, SDL_Rect source,
                                 SDL_Rect dest) {
  SDL_RenderCopy(ZeldaEng::renderer, texture, &source, &dest);
}

void textureManager::setBackground(const char *texture) {
  SDL_Texture *tex = IMG_LoadTexture(ZeldaEng::renderer, texture);

  int screenWidth;
  int screenHeight;

  SDL_GetRendererOutputSize(ZeldaEng::renderer, &screenWidth, &screenHeight);

  SDL_Rect destination = {0, 0, screenWidth, screenHeight};

  SDL_RenderCopy(ZeldaEng::renderer, tex, NULL, &destination);

  // SDL_RenderPresent(ZeldaEng::renderer);
}
