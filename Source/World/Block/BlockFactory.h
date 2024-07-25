#pragma once

#include "../../Utils/Patterns/SingleTon.h"
#include "BlockContribute.h"


class BlockFactory : public SingleTon {
public :
	static BlockFactory* _pBlockFactory;
	static BlockFactory* GetInstance();
	Block* CreateBlock(BlockType, glm::vec3);
	~BlockFactory();
};