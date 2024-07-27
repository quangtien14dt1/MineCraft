#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include "../../glm.h"
#include "../Chunk/Chunk.h"
#include "../../glm.h"

static const glm::vec3 DEFAULT_ROTATION{ 0,0,0 };

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
	glm::vec3 _position;

	BlockKey(float x, float y, float z) : _position(x, y, z) {}

	BlockKey(const glm::vec3& p) : _position(p) {}

	glm::vec3 GetKey() const { return _position; }

	bool operator==(const BlockKey& other) const {
		return _position == other._position;
	}
};

/* overide hashcode for class BlockKey */
namespace std {
	template <>
	struct hash<BlockKey> {
		std::size_t operator()(const BlockKey& k) const {
			return ((std::hash<float>()(k._position.x)
				^ (std::hash<float>()(k._position.y) << 1)) >> 1)
				^ (std::hash<float>()(k._position.z) << 1);
		}
	};
}

