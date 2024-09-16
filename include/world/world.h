#pragma once

#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <algorithm>
#include "world/worldcontant.h"
#include "world/noicegenerator.h"

class Chunk;
class ChunkModelBuilder;
class BlockFactory;
class QuadTexture;
class CubeTexture;
class ModelRender;
class Camera;

class Key {
public:
    int x, y;

    Key(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

    bool operator==(const Key& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<Key> {
        std::size_t operator()(const Key& k) const {

            std::size_t h1 = std::hash<int>{}(k.x);
            std::size_t h2 = std::hash<int>{}(k.y);
            return h1 ^ (h2 << 1); 
        }
    };
}


class World {
public:
    ~World();
	World();

    Chunk* getChunk(int x, int z);

    std::unordered_map<Key, Chunk*>& getChunksMap();

    void  createChunkMap();

    bool isChunkLoadedAt(int x, int z) const;

    bool isChunkExistsAt(int x, int z) const;

    void loadChunk(int x, int z);

    void unloadChunk(int x, int z);

    std::array<int, CHUNK_AREA> heightmapGenerator(int x, int z);

    sf::Vector2i getChunkLocation(int);

    void buildChunkMapModel(ChunkModelBuilder* , ModelRender* );

    void WorldRender(ModelRender* , Camera* );

private:

    // random noice ?
    NoiseGenerator _noice{ 30 };

    std::unordered_map<Key, Chunk*> _chunks;

    CubeTexture* _cubeTexture;

};