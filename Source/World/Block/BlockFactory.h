#pragma once

#include "../../Utils/Patterns/SingleTon.h"
#include "BlockContribute.h"


class BlockFactory : public SingleTon {
public :
	static BlockFactory* _pBlockFactory;
	static BlockFactory* GetInstance();
	Block* CreateBlock(BlockId, glm::vec3);
	~BlockFactory();
};