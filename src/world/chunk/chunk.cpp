#include "world/chunk/Chunk.h"
#include "world/block/blockdatabase.h"
#include "world/block/blockfactory.h"
#include "world/chunk/chunkmodel.h"
#include <random>
#include <iostream>

Chunk::Chunk(sf::Vector3i location)
    : _chunkId(location)
{ 
    resetBlockChunk();

    _chunkModel = new ChunkModel();
}

Chunk::~Chunk() { 

    if (_chunkModel != NULL) {

        delete _chunkModel;

        _chunkModel = NULL;

    }
};

/*
* block type configuration
*/
void Chunk::SetBlockType(int x, int y, int z, BlockType type) {
    try {

        Block* block = GetBlockByLocation(x, y, z);

        BlockFactory* factory = BlockFactory::GetInstance();

        factory->PointToBlockType(type, &block);

        _blocks[x][y][z] = block;

    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

};

/*
* Checking if location is valid inside chunk'area
* block go from 0 to ( CHUNK_SIZE - 1 )
*
*/
bool Chunk::isLocationValidate(int x, int y, int z) {

    if ((x >= CHUNK_SIZE || x < 0)) {
        return false;
    }
    else if ((y >= CHUNK_SIZE || y < 0)) {
        return false;
    }
    else if ((z >= CHUNK_SIZE || z < 0)) {
        return false;
    }

    return true;
};

/*
* function setup all chunk'block
* my height map and type 
* 
*/
void Chunk::BlocksConfiguration() {

    for (int x = 0; x < CHUNK_SIZE; ++x) {

        for (int z = 0; z < CHUNK_SIZE; ++z) {

            /*
            * h = CHUNK_SIZE 
            * because _blocks has volumn 
            * equal to CHUNK_SIZE
            */
            int h = GetHeight(x, z) % 16;

            for (int y = 0; y < h; ++y) {

                /*
                * those block that not set type
                * consider that is NULL pointer
                * point to nothing . ignore when render
                */
                if (y == h - 1) {

                    SetBlockType(x, y, z, BlockType::Grass);

                }
                else if (y > h - 3) {

                    SetBlockType(x, y, z, BlockType::Dirt);

                }
                else {

                    SetBlockType(x, y, z, BlockType::Stone);

                }

            }


        }

    }

};

void Chunk::SetChunkHeightMap(std::array<int, CHUNK_AREA > h) { _heighMap = h; };

sf::Vector3i Chunk::GetChunkLocation()const { return _chunkId; };

/*
* return block of chunk which is and pointer
* point to an block of BlockFactory
*
*/
Block* Chunk::GetBlockByLocation(int x, int y, int z) {

    if (isLocationValidate(x, y, z)) {

        return _blocks[x][y][z];

    }
    
    return NULL;
};

/*
* function reset all block of chunk
* we point to NULL
*/
void Chunk::resetBlockChunk() {

    for (int x = 0; x < CHUNK_SIZE; ++x)
    for (int y = 0; y < CHUNK_SIZE; ++y)

            for (int z = 0; z < CHUNK_SIZE; ++z) {

                _blocks[x][y][z] = NULL;

            }

};

void Chunk::SetChunkLocation(sf::Vector3i l ) { _chunkId = l; };

int Chunk::GetHeight(int x, int z) {

    int pixel = x * CHUNK_SIZE + z;

    return _heighMap[pixel];

};

ChunkModel* Chunk::GetChunkModel() { return _chunkModel; };

/* i dont know this shit @@ , never use before */
int Chunk::GenerateRandomId() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(1, 1000000);
    return dist(mt);
}
