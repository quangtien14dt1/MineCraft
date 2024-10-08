#pragma once

#include "utils/Patterns/SingleTon.h"
#include "BlockContribute.h"
#include <array>


class BlockFactory : public SingleTon {
public :
	BlockFactory();
	static BlockFactory* _pBlockFactory;
	static BlockFactory* GetInstance();
	void PointToBlockType(BlockType, Block** );
	~BlockFactory();
	std::array<Block*, static_cast<size_t>(BlockType::NUM_TYPES) >  _blocksType;
};