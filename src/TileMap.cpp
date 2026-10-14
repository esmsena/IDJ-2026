#include "TileMap.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Camera.h"
#include "GameObject.h"
#include "TileSet.h"

namespace {
// Quanto cada camada abaixo da ultima fica "mais longe" da camera.
// A ultima camada acompanha a camera (fator 1); as de baixo andam mais devagar.
const float PARALLAX_STEP = 0.5f;
}

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

    // Sprite::Render ja desconta Camera::pos inteira; somamos de volta a parte
    // que essa camada nao deve acompanhar.
    const float parallax = ParallaxFactor(layer);
    const float offsetX = Camera::pos.x * (1.0f - parallax);
    const float offsetY = Camera::pos.y * (1.0f - parallax);

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            const int tile = At(x, y, layer);
            if (tile >= 0) {
                tileSet->RenderTile(static_cast<unsigned>(tile),
                    associated.box.x + x * tileSet->GetTileWidth() + offsetX,
                    associated.box.y + y * tileSet->GetTileHeight() + offsetY);
            }
        }
    }
}

float TileMap::ParallaxFactor(int layer) const {
    const float factor = 1.0f - (mapDepth - 1 - layer) * PARALLAX_STEP;
    return factor > 0.0f ? factor : 0.0f;
}

int TileMap::GetWidth() const { return mapWidth; }
int TileMap::GetHeight() const { return mapHeight; }
int TileMap::GetDepth() const { return mapDepth; }
