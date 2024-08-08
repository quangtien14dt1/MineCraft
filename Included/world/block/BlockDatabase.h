#pragma once

#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include ".././Utils/Patterns/SingleTon.h"
#include "World/Block/BlockContribute.h"
#include "World/Block/BlockFactory.h"
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

	void AddBlock( const sf::Vector3f& ,Block* );

	void AddBlocksByChunkId(
		const ChunkKey&,
		std::vector< Block* >&
	);

	void AddBlocksByChunkId(const sf::Vector3f&, 
		std::vector< Block* > );
	
	void CleanDatabase();

	void CreateDefaultCubeModel();

	std::vector<GLfloat>
		GetTextureCoords( const Block* );

	void RemoveBlockByLocation( const sf::Vector3f& );

	Block* FindBlocksByChunkKey( const sf::Vector3f& ) const;

	std::vector< Block* >  GetAllBlocks() const;

	BlockDatabase* operator()();

	BlockDatabase();

	CubeTexture* GetTexture();

	Model* GetModel();

	size_t CheckingSize();

	// loader
	// writer
	
private:

	void RemoveBlocksByChunkIds(const ChunkKey&);

	void UpdateChunkBlock(
		 const ChunkKey&,
		 std::vector< Block* >& );

	void UpdateChunkBlock(
		 const sf::Vector3f&,
		 std::vector< Block* >& );

	static BlockDatabase* _pBlockDatabase;
	CubeTexture*	_cubeTexture;
	Model*			_cubeModel;

	/* chunk location / blocks of that chunk */
	std::unordered_map< 
		ChunkKey, std::vector< Block* > 
	> _blockStore;

	//std::vector< Block* > _blockStore;
	
};

