#include "BlockFactory.h"

BlockFactory* BlockFactory::_pBlockFactory = nullptr;

Block* BlockFactory::CreateBlock(BlockType id, glm::vec3 l) {
	Block* block = nullptr;
	switch (id) {
		case BlockType::Air:
			block = new Block();
			block->id = id;
			block->texTopCoords = { 0,0 };
			block->texSideCoords = { 0,0 };
			block->texBottomCoords = { 0,0 };
			return block;

		case BlockType::Dirt:
			block = new Block();
			block->id = id;
			block->texTopCoords = { 2 ,0 };
			block->texSideCoords = { 2 ,0 };
			block->texBottomCoords = { 2 ,0 };
			return block;

		case BlockType::Grass:
			block = new Block();
			block->id = id;
			block->texTopCoords = { 0,0 };
			block->texSideCoords = { 1,0 };
			block->texBottomCoords = { 2,0 };
			return block;

		case BlockType::Stone:
			block = new Block();
			block->id = id;
			block->texTopCoords = { 3,0 };
			block->texSideCoords = { 3,0 };
			block->texBottomCoords = { 3,0 };
			return block;

	}

	if ( block == NULL) {
		throw std::runtime_error("Failed create new block type : ");
	}

};

BlockFactory* BlockFactory::GetInstance() {

		if (_pBlockFactory == nullptr) {
			_pBlockFactory = new BlockFactory();
		}
		return _pBlockFactory;
};

BlockFactory::~BlockFactory() { 
	if (_pBlockFactory != NULL) {
		delete _pBlockFactory;
		_pBlockFactory = nullptr;
	}
}