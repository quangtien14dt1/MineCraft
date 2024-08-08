#pragma once

#include "utils/Patterns/SingleTon.h"
#include "BlockContribute.h"


class BlockFactory : public SingleTon {
public :
	static BlockFactory* _pBlockFactory;
	static BlockFactory* GetInstance();
	Block* CreateBlock(BlockType, sf::Vector3i, sf::Vector2i);
	~BlockFactory();
};