#include "world/chunk/chunkmeshbuilder.h"
#include "world/worldcontant.h"
#include "world/chunk/chunk.h"
#include "world/block/blockcontribute.h"
#include "world/block/blockdatabase.h"
#include "world/chunk/chunkmesh.h"

namespace BlockFaces {
	const std::vector<GLfloat> frontFace
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
	};

	const std::vector<GLfloat> backFace
	{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
	};

	const std::vector<GLfloat> leftFace
	{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,
	};

	const std::vector<GLfloat> rightFace
	{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
	};

	const std::vector<GLfloat> topFace
	{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,
	};

	const std::vector<GLfloat> bottomFace
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};
}

struct Direction {
	/* actualy call xyz is center of an cube
	* so direction is another center of cubes
	* next to this cube
	*/
	void update(int x, int y, int z) {
		up		= { x, y + 1, z };
		down	= { x, y - 1, z };
		left	= { x - 1, y, z };
		right	= { x + 1, y, z };
		front	= { x, y, z + 1 };
		back	= { x, y, z - 1 };
	};
	sf::Vector3i up;
	sf::Vector3i down;
	sf::Vector3i left;
	sf::Vector3i right;
	sf::Vector3i front;
	sf::Vector3i back;
};

ChunkMeshBuilder::ChunkMeshBuilder()
{

}

ChunkMeshBuilder* ChunkMeshBuilder::GetInstance() {
	if (_pChunkMeshBuilder == nullptr) {
		_pChunkMeshBuilder = new ChunkMeshBuilder();
	}
	return _pChunkMeshBuilder;
};


void ChunkMeshBuilder::BuildMesh(ChunkMesh& m, Chunk& c) {
	_chunkMesh = &m;
	_chunk = &c;

	Direction direction;
	for (int y = 0; y < CHUNK_SIZE; ++y)
		for (int x = 0; x < CHUNK_SIZE; ++x)
			for (int z = 0; z < CHUNK_SIZE; ++z) {

				Block*  block = _chunk->GetBlockByLocation(x,y,z);
				if (block == NULL) {
					continue;
				}

				direction.update(x,y,z);
				
				AddFaceToMesh(BlockFaces::topFace,		block->texTopCoords,	block, direction.up);
				AddFaceToMesh(BlockFaces::bottomFace,	block->texBottomCoords, block, direction.down);
				AddFaceToMesh(BlockFaces::leftFace,		block->texSideCoords,	block, direction.left);
				AddFaceToMesh(BlockFaces::rightFace,	block->texSideCoords,	block, direction.right);
				AddFaceToMesh(BlockFaces::frontFace,	block->texSideCoords,	block, direction.front);
				AddFaceToMesh(BlockFaces::backFace,		block->texSideCoords,	block, direction.back);
			}
};

void ChunkMeshBuilder::AddFaceToMesh(
	const std::vector<GLfloat>& blockFace, // vertices
	const sf::Vector2f& textureCoords,		// texture 
	const Block* blockPosition, // to chunk 
	const sf::Vector3i& nextDoorBlock)
{
	/*
	* so world map be 16x16 2d , each be a chunk 
	* and from above look down , each chunk contain 16x16 block 
	*/
	if (CheckingShouldAddFace(nextDoorBlock, blockPosition )) {
		auto  texCoords = BlockDatabase::GetInstance()->GetTextureCoords(blockPosition);

		_chunkMesh->AddFace( blockFace, texCoords, blockPosition, nextDoorBlock);

	}
};

bool ChunkMeshBuilder::CheckingShouldAddFace(
	const sf::Vector3i& nextDoorBlock,
	const Block* block
) 
{
	Block* block = _chunk->GetBlockByLocation(
		nextDoorBlock.x,
		nextDoorBlock.y,
		nextDoorBlock.z
	);

	if (block == NULL) {
		return true;
	}
	else return false;
};


ChunkMeshBuilder* ChunkMeshBuilder::operator()() {
	return GetInstance();
};
