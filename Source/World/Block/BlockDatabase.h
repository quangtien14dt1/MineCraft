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

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

class BlockDatabase : public SingleTon{

public:
	static BlockDatabase* GetInstance();

	
	~BlockDatabase();

	const Block* GetBlock(BlockType id) const;

	const Block* GetBlockId(BlockType id) const;

	void AddBlock( const sf::Vector3i& ,Block* );

	void CleanDatabase();

	void CreateDefaultCubeModel();

	std::vector<GLfloat>
		GetTextureCoords(Block* );

	void RemoveBlockByLocation( const sf::Vector3i& );

	std::vector<Block*, Model*> 
		GetAllBlockById(const BlockType) const;


	Block* FindBlockByLocation( const sf::Vector3i& ) const;

	std::unordered_map< int, 
						std::unordered_map<std::pair<int, int>, 
						Block*, pair_hash > > 
		GetAllBlocks() const;

	BlockDatabase* operator()();

	BlockDatabase();

	CubeTexture* GetTexture();

	Model* GetModel();

	size_t CheckingSize();
	
private:

	static BlockDatabase* _pBlockDatabase;
	CubeTexture*	_cubeTexture;
	Model*			_cubeModel;

	std::unordered_map< int , std::unordered_map < 
		std::pair< int, int > , Block*, pair_hash >
	> _blockStore;

	//std::vector< Block* > _blockStore;
	
};

