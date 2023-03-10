#include "../include/core.h"
#include <fstream>

tilemap::tilemap() {}

tilemap::~tilemap() {}

void tilemap::LoadTilemap(std::string path, int sizeX, int sizeY) {
  char tile;
  std::fstream tilemapFile;
  tilemapFile.open(path);

  for (int y = 0; y < sizeY + 1; y++) {
    for (int x = 0; x < sizeX + 1; x++) {
      tilemapFile.get(tile);
      ZeldaEng::AddTile(atoi(&tile), x * 32, y * 32);
      tilemapFile.ignore();
    }
  }

  tilemapFile.close();
}
