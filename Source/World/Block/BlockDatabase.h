#pragma once

#include <array>
#include <vector>
#include <map>
#include ".././Utils/Patterns/SingleTon.h"
#include "../World/Block/BlockContribute.h"
#include "../World/Block/BlockFactory.h"
#include "../../Texture/CubeTexture.h"

class Model;

class BlockDatabase : public SingleTon{

public:
	static BlockDatabase* GetInstance();

	
	~BlockDatabase();

	const Block& GetBlock(BlockId id) const;

	const Block& GetBlockId(BlockId id) const;

	void AddBlock( Block* );

	void RemoveBlock( const glm::vec3 );

	std::vector<Block*, Model*> 
		GetAllBlockById(const BlockId) const;


	Block* FindBlockByLocation( const glm::vec3 ) const;

	std::vector< std::pair<Block*, Model*> > GetAllBlocks() const;

	void RemoveBlockByLocation(const glm::vec3&);

	BlockDatabase* operator()();

	BlockDatabase();

	CubeTexture* GetTexture();
	
private:

	

	static BlockDatabase* _pBlockDatabase;

	CubeTexture* _cubeTexture;

	std::vector< std::pair<Block*, Model*> > _blockStore;

	
};