#ifndef TILE_SET_H
#define TILE_SET_H

#include <string>

#include "Sprite.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, const std::string& file);

    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth() const;
    int GetTileHeight() const;

private:
    Sprite tileSet;
    int tileWidth;
    int tileHeight;
    int tileCount;
};

#endif
