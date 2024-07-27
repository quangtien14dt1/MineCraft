#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include "../../glm.h"
#include "../Chunk/Chunk.h"
#include "../../glm.h"

class Chunk;

using Block_t = uint8_t;

enum class BlockType : Block_t {
	Air		= 0,
	Grass	= 1,
	Dirt	= 2,
	Stone	= 3,

	NUM_TYPES
};

struct Block {

	sf::Vector2f texTopCoords;
	sf::Vector2f texSideCoords;
	sf::Vector2f texBottomCoords;

	BlockType id;
	sf::Vector2i chunkId;

};

class BlockKey {
public:

	sf::Vector3i _position;

	BlockKey(float x, float y, float z) : _position(x, y, z) {};

	BlockKey(const sf::Vector3i& p) : _position(p) {};

	bool operator==(const sf::Vector3i l) const {
		return _position == l;
	}
};

