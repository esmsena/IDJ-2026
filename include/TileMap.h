#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <memory>
#include <string>
#include <vector>

#include "Component.h"

class TileSet;

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);

    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void Update(float dt) override;
    void Render() override;
    void RenderLayer(int layer);
    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;

private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif
