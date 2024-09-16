#include "world/world.h"
#include "world/chunk/chunk.h"
#include "world/chunk/chunkmodel.h"
#include "texture/quadtexture.h"
#include "texture/cubetexture.h"
#include "renderer/baserender.h"
#include "renderer/modelsrender.h"
#include "world/chunk/chunkmodelbuilder.h"


World::~World() {

    if (_cubeTexture != NULL) {
        delete _cubeTexture; _cubeTexture = nullptr;
    }

};

World::World() {

    _cubeTexture = new CubeTexture();

    _cubeTexture->SetupCubeImage("DefaultPack2");

};

std::unordered_map<Key, Chunk*>& 
World::getChunksMap() { return _chunks; };

void World::createChunkMap() {

    for (int x = 0; x < CHUNK_SIZE; x++) {

        for (int z = 0; z < CHUNK_SIZE; z++) {

            if (!isChunkExistsAt(x, z))
            {
                Key    key{ x, z };
                Chunk*  chunk = new Chunk({ x, 0, z });
                chunk->SetChunkHeightMap( heightmapGenerator(x,z) );
                _chunks.emplace(key, std::move(chunk));
            }

        }

    }

};

void World::buildChunkMapModel(ChunkModelBuilder* b, ModelRender* r) {

    for (int x = 0; x < CHUNK_SIZE; x++) 
    for (int z = 0; z < CHUNK_SIZE; z++) {

        Chunk* chunk = getChunk(x, z);

        chunk->BlocksConfiguration();

        ChunkModel* chunkModel = new ChunkModel();

        b->BuildMesh(*chunkModel, *chunk, *_cubeTexture);

        r->AddModel(chunkModel);

    }

};


Chunk* World::getChunk(int x, int z) {

    Key query( x,z );

    return _chunks.at(query);
};

bool World::isChunkExistsAt(int x, int z) const {

    Key query(x, z);

	return _chunks.find(query) != _chunks.end();

};

bool World::isChunkLoadedAt(int x, int z) const {
    /*if (!chunkExistsAt(x, z)) {
        return false;
    }*/
    return true;
};


void World::loadChunk(int x, int z) { getChunk(x,z); };

void World::unloadChunk(int x, int z) { };

sf::Vector2i World::getChunkLocation(int l) {
    int row = l / CHUNK_SIZE;  // row 
    int col = l % CHUNK_SIZE;  // column

    return sf::Vector2i{row, col};
};

std::array<int, CHUNK_AREA> 
World::heightmapGenerator(int mapx, int mapz) {

    std::array<int, CHUNK_AREA> map;

    /*
    * world map by 16x16 chunk 
    * by pixel , it should be 256 x 256 picxel 
    * 
    */    
    for (int localX = 0; localX < CHUNK_SIZE; localX++) {

        for (int localZ = 0; localZ < CHUNK_SIZE; localZ++) {

            int h = _noice.getHeight(localX, localZ, mapx, mapz);

            map[localX * CHUNK_SIZE + localZ] = h;

        }

    }

    return map;

};

void World::WorldRender(ModelRender* r, Camera* c) {

    r->RenderModels(c, _cubeTexture);

};
