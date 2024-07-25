#include "BlockDatabase.h"
#include "../Entity/Model.h"
#include "../World/Block/BlockContribute.h"
#include <iostream>

static BlockDatabase* _pBlockDatabase;

BlockDatabase* BlockDatabase::_pBlockDatabase = nullptr;

BlockDatabase::BlockDatabase() {

	std::cout << "Create cube image ..." << std::endl;
	_cubeTexture = new CubeTexture();

	std::cout << "Load DefaultPack texture..." << std::endl;
	_cubeTexture->SetupCubeImage("DefaultPack");

}

BlockDatabase::~BlockDatabase() {
	if (_cubeTexture) {
		delete _cubeTexture;
		_cubeTexture = nullptr;
	}
	
	for (auto& block : _blockStore) {
		if (block) {
			delete block;
			block = nullptr;
		}
	}

	if (_pBlockDatabase != nullptr) {
		delete _pBlockDatabase;
		_pBlockDatabase = nullptr;
	}
}
int BlockDatabase::CheckingSize() {
	return _blockStore.size();
}


BlockDatabase* BlockDatabase::operator()() {
	return GetInstance();
};

BlockDatabase* BlockDatabase::GetInstance() {
	if (_pBlockDatabase == nullptr) {
		_pBlockDatabase = new BlockDatabase();
	}
	return _pBlockDatabase;
};


void BlockDatabase::AddBlock( Block* b) {
	
	_blockStore.push_back( b );

};

void BlockDatabase::CreateDefaultCubeModel() {
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

	_cubeModel = new Model();
	_cubeModel->addData({ vertexCoords, texCoords, indices });
}

Model* BlockDatabase::GetModel() { return _cubeModel; };

void BlockDatabase::RemoveBlock(const glm::vec3 l) {
	_blockStore.erase(
		std::remove_if(_blockStore.begin(), _blockStore.end(), 
			[&l](const Block* ptr) {
				return ptr->cubeLocation == l;
			}),
		_blockStore.end()
	);
};


CubeTexture* BlockDatabase::GetTexture() { return _cubeTexture; };

Block* BlockDatabase::FindBlockByLocation(const glm::vec3 l) const {
	auto it = std::find_if(_blockStore.begin(), _blockStore.end(),
		[&l](const auto& block) {
			return block->cubeLocation == l;
		});

	if (it != _blockStore.end()) {
		return *it;
	}

	return nullptr;
}

std::vector < Block* >
BlockDatabase::GetAllBlocks() const {
	return _blockStore;
};
