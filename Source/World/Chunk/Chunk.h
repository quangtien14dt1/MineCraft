#pragma once

#include <SFML/Graphics.hpp>
#include "../WorldContant.h"
#include "../Block/BlockContribute.h"
#include <vector>

/* 
  make play ground ( x, y)  and z is ladder to sky
*/

class BlockDatabase;

class Chunk {
public:
	Chunk();
	~Chunk();

	void SetBlockType(int x, int y, int z, uint8_t);

	bool OutOfBound(int value , int direction);

	/* chunk maintanance */
	void CreateChunk();

	/* generator  */
	void ProcessPosition(const sf::Vector3i& );


private:

	static int GenerateRandomId();
	int _chunkId;
	
};