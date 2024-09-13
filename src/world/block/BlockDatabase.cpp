#include <iostream>
#include "basemodel.h"
#include "world/Block/blockcontribute.h"
#include "world/Block/blockdatabase.h"


static BlockDatabase* _pBlockDatabase;

BlockDatabase* BlockDatabase::_pBlockDatabase = nullptr;

BlockDatabase::BlockDatabase() 
	: _cubeModel{NULL}
{

	_cubeTexture = new CubeTexture();

	_cubeTexture->SetupCubeImage("DefaultPack");
}

BlockDatabase::~BlockDatabase() {
	if (_cubeTexture) {
		delete _cubeTexture;
		_cubeTexture = nullptr;
	}

	if (_pBlockDatabase != nullptr) {
		delete _pBlockDatabase;
		_pBlockDatabase = nullptr;
	}
	
	CleanDatabase();

}
size_t BlockDatabase::CheckingSize() {
	return _blockStore.size();
}


BlockDatabase* BlockDatabase::operator()() {
	return GetInstance();
};

void BlockDatabase::CleanDatabase() {
	/* think this only make sence when 
	we load blocks from database 
	*/
	for (auto& chunkKey : _blockStore) {
		for (auto& block : chunkKey.second) {

			delete block;
		}
		chunkKey.second.clear();
	}
	_blockStore.clear();
}

BlockDatabase* BlockDatabase::GetInstance() {
	if (_pBlockDatabase == nullptr) {
		_pBlockDatabase = new BlockDatabase();
	}
	return _pBlockDatabase;
};

void 
BlockDatabase::AddBlocksByChunkId(
	const sf::Vector3f& p, 
	std::vector< Block* > blocks) 
{
	ChunkKey key(p);
	UpdateChunkBlock(key , blocks);

}

void BlockDatabase::AddBlocksByChunkId(
	const ChunkKey& k,
	std::vector< Block* >& blocks
) {
	UpdateChunkBlock(k, blocks);
};

void BlockDatabase::RemoveBlocksByChunkIds(
	 const ChunkKey& k) 
{
	auto it = _blockStore.find(k);
	if (it != _blockStore.end()) {
		for (Block* block : it->second) {
			delete block;
		}
	}
	_blockStore.erase(it);
}; 


void BlockDatabase::UpdateChunkBlock (
	 const ChunkKey& k,
	 std::vector< Block* >& blocks ) 
{
	auto it = _blockStore.find(k);
	if( it != _blockStore.end()) {
		RemoveBlocksByChunkIds( k );
		_blockStore[k] = blocks;
	}
	else {
		_blockStore[k] = blocks;
	}
}

void BlockDatabase::UpdateChunkBlock(
	 const sf::Vector3f& l,
	 std::vector< Block* >& blocks ) 
{
	ChunkKey key(l);
	auto it = _blockStore.find(key);
	if (it != _blockStore.end()) {
		RemoveBlocksByChunkIds(key);
		_blockStore[key] = blocks;
	}
	else {
		_blockStore[key] = blocks;
	}
};

void BlockDatabase::AddBlock(const sf::Vector3f& p,Block* b) {};

void BlockDatabase::CreateDefaultCubeModel(Model* m) {
	std::vector<GLuint> indices
	{

		//        7--------6	| Y
		//       /|       /|	| |
		//      0--------1 |	| |_________
		//      | |      | |	| |			|
		//	    | 3------|-2	| |			| 
		//	    | /      | /	| |			|
		//	    |/       |/		| |			|
		//      3--------2		| |_________|_______X

		// back
		0, 1, 2,
		2, 3, 0,

		// front
		4, 5, 6,
		6, 7, 4,

		// right 
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,

		// top 
		16, 17, 18,
		18, 19, 16,

		// bottom
		20, 21, 22,
		22, 23, 20
	};

	std::vector<GLfloat> vertexCoords
	{
		// back
		1, 0, 0, //0       2--------3	| Y
		0, 0, 0, //1      /|       /|	| |
		0, 1, 0, //2     7--------6 |	| 1_________1
		1, 1, 0, //3     | |      | |	| |		  / |
				 //      | 1------|-0	| |		/	| 
				 //	     | /      | /	| |	  /	    |
		// front //	     |/       |/	| |	/		|
		0, 0, 1, //4     4--------5		| 0_________1_______X
		1, 0, 1, //5     
		1, 1, 1, //6
		0, 1, 1, //7

		// right
		1, 0, 1, //8
		1, 0, 0, //9
		1, 1, 0, //10
		1, 1, 1, //11

		// left
		0, 0, 0, //12
		0, 0, 1, //13
		0, 1, 1, //14
		0, 1, 0, //15

		// top
		0, 1, 1, //16
		1, 1, 1, //17
		1, 1, 0, //18
		0, 1, 0, //19

		// bottom
		0, 0, 0, //20
		1, 0, 0, //21
		1, 0, 1, //22
		0, 0, 1  //23
	};

	/* Default texture grass */
	auto top	= _cubeTexture->GetTexture({0,0});
	auto side	= _cubeTexture->GetTexture({1,0});
	auto bottom = _cubeTexture->GetTexture({2,0});

	std::vector<GLfloat> texCoords;
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), top.begin(), top.end());
	texCoords.insert(texCoords.end(), bottom.begin(), bottom.end());

	//_cubeModel = new BaseModel();

	//_cubeModel->AddData({ vertexCoords, texCoords, indices });
}

Model* BlockDatabase::GetModel() { return _cubeModel; };

std::vector<GLfloat>
BlockDatabase::GetTextureCoords( const Block* b) {

	auto top = _cubeTexture->GetTexture(b->texTopCoords);
	auto side = _cubeTexture->GetTexture(b->texSideCoords);
	auto bottom = _cubeTexture->GetTexture(b->texBottomCoords);

	std::vector<GLfloat> texCoords;
	texCoords.insert(texCoords.end(), top.begin(), top.end());
	texCoords.insert(texCoords.end(), bottom.begin(), bottom.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	//texCoords.insert(texCoords.end(), side.begin(), side.end());
	//texCoords.insert(texCoords.end(), side.begin(), side.end());
	//texCoords.insert(texCoords.end(), side.begin(), side.end());

	return texCoords;
};

void BlockDatabase::RemoveBlockByLocation(const sf::Vector3f& p) {

	//auto yIt = _blockStore.find( ChunkKey(p) );

	//if (yIt != _blockStore.end()) {

	//	auto xzIt = std::find_if(yIt->second.begin(), yIt->second.end(), [&p](Block* b) {
	//		return b->location.x == p.x && b->location.y == p.y;
	//		});

	//	if (xzIt != yIt->second.end()) {
	//		delete *xzIt;
	//		yIt->second.erase(xzIt);
	//	}
	//	if (yIt->second.empty()) {
	//		_blockStore.erase(yIt);
	//	}

	//}

};


CubeTexture* BlockDatabase::GetTexture() { return _cubeTexture; };

Block* BlockDatabase::FindBlocksByChunkKey(const sf::Vector3f& p) const {

	/*auto yIt = _blockStore.find( ChunkKey(p) );

	if (yIt != _blockStore.end()) {

		auto xzIt = std::find_if( yIt->second.begin(), yIt->second.end(), [&p](Block* b) {
			return b->location.x == p.x && b->location.y == p.y;
			});

		if (xzIt != yIt->second.end()) {
			return *xzIt;
		}
	}
	*/
	return nullptr;
}

std::vector< Block* > 
BlockDatabase::GetAllBlocks() const {
	std::vector<Block*> allBlocks;

	for (const auto& chunk : _blockStore) {
		for (Block* block : chunk.second) {
			allBlocks.push_back(block);
		}
	}

	return allBlocks;
};
