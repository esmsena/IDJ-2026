#include "TileMap.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "GameObject.h"
#include "TileSet.h"

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet)
    : Component(associated), mapWidth(0), mapHeight(0), mapDepth(0) {
    SetTileSet(tileSet);
    Load(file);
}

void TileMap::Load(const std::string& file) {
    std::ifstream input(file);
    if (!input.is_open() && file.rfind("Recursos/", 0) != 0) {
        input.open("Recursos/" + file);
    }
    if (!input.is_open()) {
        std::cerr << "Nao foi possivel carregar o mapa '" << file << "'.\n";
        return;
    }

    std::stringstream values;
    values << input.rdbuf();
    std::string content = values.str();
    for (char& character : content) if (character == ',') character = ' ';
    std::istringstream parser(content);

    parser >> mapWidth >> mapHeight >> mapDepth;
    if (!parser || mapWidth <= 0 || mapHeight <= 0 || mapDepth <= 0) {
        mapWidth = mapHeight = mapDepth = 0;
        tileMatrix.clear();
        return;
    }

    tileMatrix.assign(mapWidth * mapHeight * mapDepth, -1);
    for (int& tile : tileMatrix) parser >> tile;
}

void TileMap::SetTileSet(TileSet* newTileSet) {
    tileSet.reset(newTileSet);
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[x + mapWidth * (y + mapHeight * z)];
}

void TileMap::Update(float) {}

void TileMap::Render() {
    for (int layer = 0; layer < mapDepth; ++layer) RenderLayer(layer);
}

void TileMap::RenderLayer(int layer) {
    if (tileSet == nullptr || layer < 0 || layer >= mapDepth) return;

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            const int tile = At(x, y, layer);
            if (tile >= 0) {
                tileSet->RenderTile(static_cast<unsigned>(tile),
                    associated.box.x + x * tileSet->GetTileWidth(),
                    associated.box.y + y * tileSet->GetTileHeight());
            }
        }
    }
}

int TileMap::GetWidth() const { return mapWidth; }
int TileMap::GetHeight() const { return mapHeight; }
int TileMap::GetDepth() const { return mapDepth; }
