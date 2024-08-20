#include "world/block/blockfactory.h"
#include <SFML/Graphics.hpp>

BlockFactory* BlockFactory::_pBlockFactory = nullptr;

/* small type factory  menthod  
*/
BlockFactory::BlockFactory() {
	_blocksType[static_cast<size_t>(BlockType::Air)] = new AirBlock();
	_blocksType[static_cast<size_t>(BlockType::Dirt)] = new DirtBlock();
	_blocksType[static_cast<size_t>(BlockType::Grass)] = new GrassBlock();
	_blocksType[static_cast<size_t>(BlockType::Stone)] = new StoneBlock();
};

Block* BlockFactory::PointToBlockType(BlockType id) {

	switch (id) {
		case BlockType::Air:
			return _blocksType[(unsigned)BlockType::Air];
			
		case BlockType::Dirt:
			return _blocksType[(unsigned)BlockType::Dirt];

		case BlockType::Grass:
			return _blocksType[(unsigned)BlockType::Grass];

		case BlockType::Stone:
			return _blocksType[(unsigned)BlockType::Stone];

		default:
			throw std::runtime_error("Failed to creat new block type: invalid id ");

	}

};

BlockFactory* BlockFactory::GetInstance() {

		if (_pBlockFactory == nullptr) {
			_pBlockFactory = new BlockFactory();
		}
		return _pBlockFactory;
};

BlockFactory::~BlockFactory() { 

	for (auto b : _blocksType) {
		if (b != NULL) delete b;
		b = nullptr;
	}

	if (_pBlockFactory != NULL) {
		delete _pBlockFactory;
		_pBlockFactory = nullptr;
	}
}