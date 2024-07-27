#include "BlockFactory.h"
#include <SFML/Graphics.hpp>

BlockFactory* BlockFactory::_pBlockFactory = nullptr;

Block* BlockFactory::CreateBlock(BlockType id, glm::vec3 l) {

	auto createblock = [id](
		sf::Vector2f top, sf::Vector2f side, sf::Vector2f bottom
	) -> Block* {
			Block* block = new Block();
			block->id = id;
			block->texTopCoords = top;
			block->texSideCoords = side;
			block->texBottomCoords = bottom;
			return block;
	};

	switch (id) {
		case BlockType::Air:
			return createblock({ 0, 0 }, { 0, 0 }, { 0, 0 });

		case BlockType::Dirt:
			return createblock({ 2, 0 }, { 2, 0 }, { 2, 0 });

		case BlockType::Grass:
			return createblock({ 0, 0 }, { 1, 0 }, { 2, 0 });

		case BlockType::Stone:
			return createblock({ 3, 0 }, { 3, 0 }, { 3, 0 });

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
	if (_pBlockFactory != NULL) {
		delete _pBlockFactory;
		_pBlockFactory = nullptr;
	}
}