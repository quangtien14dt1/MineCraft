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

	const Block& GetBlock(BlockType id) const;

	const Block& GetBlockId(BlockType id) const;

	void AddBlock( Block* );

	void CleanDatabase();

	void CreateDefaultCubeModel();

	void RemoveBlock( const glm::vec3 );

	std::vector<Block*, Model*> 
		GetAllBlockById(const BlockType) const;


	Block* FindBlockByLocation( const glm::vec3 ) const;

	std::vector< Block* > GetAllBlocks() const;

	void RemoveBlockByLocation(const glm::vec3&);

	BlockDatabase* operator()();

	BlockDatabase();

	CubeTexture* GetTexture();

	Model* GetModel();

	int CheckingSize();
	
private:

	static BlockDatabase* _pBlockDatabase;
	CubeTexture*	_cubeTexture;
	Model*			_cubeModel;

	std::vector< Block* > _blockStore;

	
};