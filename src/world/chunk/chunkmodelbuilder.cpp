#include "world/chunk/chunkmodelbuilder.h"
#include "world/worldcontant.h"
#include "world/chunk/chunk.h"
#include "world/block/blockcontribute.h"
#include "world/block/blockdatabase.h"
#include "world/chunk/chunkmodel.h"

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
	/* 
	* actualy call xyz is center of an cube
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

ChunkModelBuilder* ChunkModelBuilder::_pChunkModelBuilder = nullptr;

ChunkModelBuilder::ChunkModelBuilder()
{ }

ChunkModelBuilder* ChunkModelBuilder::GetInstance() {
	if (_pChunkModelBuilder == nullptr) {
		_pChunkModelBuilder = new ChunkModelBuilder();
	}
	return _pChunkModelBuilder;
};


void ChunkModelBuilder::BuildMesh(ChunkModel& m, Chunk& c, CubeTexture& t) {
	_chunkModel = &m;
	_chunk = &c;
	_cubeTexture = &t;

	Direction direction;
	for (int x = 0; x < CHUNK_SIZE; ++x)
	for (int y = 0; y < CHUNK_SIZE; ++y)
	for (int z = 0; z < CHUNK_SIZE; ++z) {

		Block*  block = _chunk->GetBlockByLocation(x,y,z);
		if (block == NULL) {
			continue;
		}

		direction.update(x,y,z);
		const sf::Vector3i blocation{ x,y,z };

		AddFaceToMesh(BlockFaces::topFace, block->texTopCoords, blocation, direction.up);
		AddFaceToMesh(BlockFaces::bottomFace, block->texBottomCoords, blocation, direction.down);
		AddFaceToMesh(BlockFaces::leftFace,  block->texSideCoords, blocation, direction.left);
		AddFaceToMesh(BlockFaces::rightFace, block->texSideCoords, blocation, direction.right);
		AddFaceToMesh(BlockFaces::frontFace, block->texSideCoords, blocation, direction.front);
		AddFaceToMesh(BlockFaces::backFace, block->texSideCoords, blocation,direction.back);
	}

	_chunkModel->AddMeshToModel();

};

void ChunkModelBuilder::AddFaceToMesh(
	const std::vector<GLfloat>& blockFace, // vertices
	const sf::Vector2i& texture,
	const sf::Vector3i& bLocation,
	const sf::Vector3i& blockAdj)
{
	/*
	* so world map be 16x16 2d , each be a chunk 
	* and from above look down , each chunk contain 16x16 block 
	*/
	if (CheckingShouldAddFace(blockAdj)) {

		auto texCoords = _cubeTexture->GetTexture(texture);

		_chunkModel->AddFace(
			blockFace, 
			texCoords, 
			bLocation,
			_chunk->GetChunkLocation()
		);

	}
};

bool ChunkModelBuilder::CheckingShouldAddFace(
	const sf::Vector3i& blockAdj
	//const Block* block
) 
{
	
	Block* block = _chunk->GetBlockByLocation(
		blockAdj.x,
		blockAdj.y,
		blockAdj.z
	);

	/* next block already exist for that direction */
	if (block == NULL) {
		return true;
	}
	else return false;
};


ChunkModelBuilder* ChunkModelBuilder::operator()() {
	return GetInstance();
};
