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
	_blocksType[static_cast<size_t>(BlockType::Water)] = new WaterBlock();
};

void BlockFactory::PointToBlockType(BlockType id,Block** block) {

	switch (id) {
		case BlockType::Air:
			*block = _blocksType[(unsigned)BlockType::Air];
			break;
			
		case BlockType::Dirt:
			*block = _blocksType[(unsigned)BlockType::Dirt];
			break;

		case BlockType::Grass:
			*block = _blocksType[(unsigned)BlockType::Grass];
			break;

		case BlockType::Stone:
			*block = _blocksType[(unsigned)BlockType::Stone];
			break;

		case BlockType::Water:
			*block = _blocksType[(unsigned)BlockType::Water];
			break;

		default:
			throw std::runtime_error(
				"Failed to creat new block"
			);

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