#include "world/block/blockfactory.h"
#include <SFML/Graphics.hpp>

BlockFactory* BlockFactory::_pBlockFactory = nullptr;

/* small type factory  menthod  
*/
BlockFactory::BlockFactory() {

};

Block* BlockFactory::CreateBlock(BlockType id) {

	switch (id) {
		case BlockType::Air:
			if (!_blocksType[(unsigned)BlockType::Air]) {

				_blocksType[(unsigned)BlockType::Air] = &AirBlock();

			}
			return _blocksType[(unsigned)BlockType::Air];
			
		case BlockType::Dirt:
			if(!_blocksType[(unsigned)BlockType::Dirt]) {

				_blocksType[(unsigned)BlockType::Dirt] = &DirtBlock();

			}
			return _blocksType[(unsigned)BlockType::Dirt];

		case BlockType::Grass:
			if (!_blocksType[(unsigned)BlockType::Grass]) {

				_blocksType[(unsigned)BlockType::Grass] = &GrassBlock();

			}
			return _blocksType[(unsigned)BlockType::Grass];

		case BlockType::Stone:
			if (!_blocksType[(unsigned)BlockType::Stone]) {

				_blocksType[(unsigned)BlockType::Stone] = &StoneBlock();

			}
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