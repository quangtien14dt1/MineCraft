#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <algorithm>
#include "world/worldcontant.h"

class Chunk;
class ChunkModelBuilder;
class BlockFactory;

struct VectorXZ
{
	int x, z;
    
    bool operator==(const VectorXZ& other) const {
        return x == other.x && z == other.z;
    }
};

// overide hashmap for unorder map 
namespace std {
    template <>
    struct hash<VectorXZ> {
        std::size_t operator()(const VectorXZ& v) const noexcept {
            std::size_t h1 = std::hash<int>{}(v.x);
            std::size_t h2 = std::hash<int>{}(v.z);
            return h1 ^ (h2 << 1);
        }
    };
}

using ChunkMap = std::unordered_map<VectorXZ, Chunk>;

class World {
public:
	World(ChunkModelBuilder*, BlockFactory*);

    Chunk& getChunk(int x, int z);

    ChunkMap& getChunksMap();

    void  createChunkMap();

    bool chunkLoadedAt(int x, int z) const;
    bool chunkExistsAt(int x, int z) const;

    void loadChunk(int x, int z);
    void unloadChunk(int x, int z);

    void heightmapGenerator();

    sf::Vector2i getChunkLocation(int);

    std::array< std::array<int, CHUNK_SIZE>, CHUNK_SIZE>
        getHeightMapChunk(int x, int z);

    void buildChunkMapModel();

    BlockFactory* _blockFactory;
private:
    ChunkMap _chunks; // could just  using vector instead then 

    std::vector<Chunk> _chunkMap;

    ChunkModelBuilder* _chunkModelBuilder;


    std::array< std::array< std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_AREA> _heightMap;

};