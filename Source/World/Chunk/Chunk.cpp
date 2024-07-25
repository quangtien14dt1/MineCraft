#include "Chunk.h"
#include "../WorldContant.h"
#include "../Block/BlockDatabase.h"
#include "../Block/BlockFactory.h"
#include <random>
#include <iostream>

Chunk::Chunk() {

}

Chunk::~Chunk() {};

void Chunk::ProcessPosition(sf::Vector3i location) {

    Block* block = BlockFactory::GetInstance()->CreateBlock(
        BlockType::Stone, glm::vec3{ 
                location.x,
                location.y,
                location.z }
    );

    BlockDatabase::GetInstance()->AddBlock(block);
};

void Chunk::CreateChunk() {
    // look not very smart 
    for (int x = 0; x < CHUNK_SIZE; ++x) {

        for (int y = 0; y < CHUNK_SIZE; ++y) {

            for (int z = 0; z < 2; ++z) {

                sf::Vector3i l{x,y,z};

                ProcessPosition(l);

            }

        }
    }

    //std::cout << "size: " << 
    //    BlockDatabase::GetInstance()->CheckingSize() << std::endl;
};

/* i dont know this shit @@ , never use before */
int Chunk::GenerateRandomId() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(1, 1000000);
    return dist(mt);
}
