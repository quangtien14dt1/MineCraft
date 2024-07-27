#pragma once

#include <array>
#include <vector>
#include <map>
#include <unordered_map>
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

	void AddBlock( BlockKey ,Block* );

	void CleanDatabase();

	void CreateDefaultCubeModel();

	std::vector<GLfloat>
		GetTextureCoords(Block* );

	void RemoveBlock( const BlockKey& );

	std::vector<Block*, Model*> 
		GetAllBlockById(const BlockType) const;


	Block* FindBlockByLocation( const BlockKey& ) const;

	std::unordered_map< BlockKey, Block* > GetAllBlocks() const;

	void RemoveBlockByLocation(const glm::vec3&);

	BlockDatabase* operator()();

	BlockDatabase();

	CubeTexture* GetTexture();

	Model* GetModel();

	size_t CheckingSize();
	
private:

	static BlockDatabase* _pBlockDatabase;
	CubeTexture*	_cubeTexture;
	Model*			_cubeModel;

	std::unordered_map< BlockKey , Block* > _blockStore;
	//std::vector< Block* > _blockStore;

	
};