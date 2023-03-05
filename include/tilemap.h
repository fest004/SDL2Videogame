#include "zeldaEng.h"

#ifndef tilemap_h
#define tilemap_h

class tilemap {
public:
  tilemap();
  ~tilemap();

  // Basic tilemap with 20 * 25 tiles
  void LoadTilemap(int array[20][25]);
  void DrawTileMap();

private:
  SDL_Rect source, destination;

  // Declaring different textures in the game
  SDL_Texture *textureMissing;
  SDL_Texture *ground1;
  SDL_Texture *platform2;

  int map[20][25];
};

#endif
