#include "world/world.h"
#include "world/chunk/chunk.h"
#include "world/chunk/chunkmodel.h"
#include "world/noicegenerator.h"

World::World(ChunkModelBuilder* b, BlockFactory* f)
    :_chunkModelBuilder(b) , _blockFactory(f)
{};

ChunkMap& World::getChunksMap() {
	return _chunks;
};

Chunk& World::getChunk(int x, int z) {
    VectorXZ query = { x,z };

    return _chunks.at(query);
};

/*
* 
*/
bool World::chunkExistsAt(int x, int z) const {
	return _chunks.find({ x,z }) != _chunks.end();
};

void World::createChunkMap() {

    for (int x = 0; x < CHUNK_SIZE; x++) {

        for (int z = 0; z < CHUNK_SIZE; z++) {

            if (!chunkExistsAt(x, z))
            {
                //VectorXZ    key{ x, z };
                //Chunk       chunk{ {x, z}, new ChunkModel(), this };
                //_chunks.emplace(key, std::move(chunk));
            }

        }

    }
    
};

void World::buildChunkMapModel() {

    for (int x = 0; x < CHUNK_SIZE; x++) {

        for (int z = 0; z < CHUNK_SIZE; z++) {

            //if ( getChunk(x, z).isLoaded() ) {
;
                Chunk chunk = getChunk(x, z);

                //chunk.CreateChunk(_heightMap[ x * CHUNK_SIZE + z]);

                //chunk.BuildMeshModel(_chunkModelBuilder);

            //}

        }

    }
};

bool World::chunkLoadedAt(int x, int z) const {
    if (!chunkExistsAt(x, z)) {
        return false;
    }
};

void World::loadChunk(int x, int z) { getChunk(x,z); };

void World::unloadChunk(int x, int z) { 
    // 
};

sf::Vector2i World::getChunkLocation(int l) {
    int row = l / CHUNK_SIZE;  // row 
    int col = l % CHUNK_SIZE;  // column

    return sf::Vector2i{row, col};
};

std::array< std::array<int, CHUNK_SIZE>, CHUNK_SIZE>
World::getHeightMapChunk(int x, int z) {

    int chunkLocation = x * CHUNK_SIZE + z;

    return _heightMap[chunkLocation];
};

void World::heightmapGenerator() {

    // random noice ?
    NoiseGenerator noice(30);

    /*
    * world map by 16x16 chunk 
    * by pixel , it should be 256 x 256 picxel 
    * 
    */
    for (int chunk = 0; chunk < CHUNK_AREA; chunk++) {

        int row = chunk / CHUNK_SIZE;  // row 
        int col = chunk % CHUNK_SIZE;  // column

            // block location x/z
             
        for (int localX = 0; localX < CHUNK_SIZE; localX++) {

            for (int localZ = 0; localZ < CHUNK_SIZE; localZ++) {

                int h = noice.getHeight(localX, localZ, row, col);

                _heightMap[chunk][localX][localZ] = h;
            }

        }

    }

};
