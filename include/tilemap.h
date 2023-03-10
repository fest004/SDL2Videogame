#include <string>

#ifndef tilemap_h
#define tilemap_h

class tilemap {
public:
  tilemap();
  ~tilemap();

  static void LoadTilemap(std::string path, int sizeX, int sizeY);
private:
};

#endif
