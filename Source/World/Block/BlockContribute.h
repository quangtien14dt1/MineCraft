#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
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

	glm::vec3 cubeLocation;
	glm::vec3 cubeRotation;

	BlockType id;
	sf::Vector2i chunkId;

};

