#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include "glm.h"
#include "world/chunk/chunk.h"

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
	/* block' type */
	BlockType id;

	/* cube textures coords */
	sf::Vector2f texTopCoords;
	sf::Vector2f texSideCoords;
	sf::Vector2f texBottomCoords;

	/* internal location block to chunk */
	sf::Vector3i location;

	/* chunk location to world map */
	sf::Vector2i chunkId;

};

class ChunkKey {
public:
	sf::Vector3f _position;

	ChunkKey(float x, float y, float z) : _position(x, y, z) {}

	ChunkKey(const sf::Vector3f& p) : _position(p) {}

	sf::Vector3f GetKey() const { return _position; }

	bool operator==(const ChunkKey& other) const {
		return _position == other._position;
	}
};

/* overide hashcode for class BlockKey */
namespace std {
	template <>
	struct hash<ChunkKey> {
		std::size_t operator()(const ChunkKey& k) const {
			return ((std::hash<float>()(k._position.x)
				^ (std::hash<float>()(k._position.y) << 1)) >> 1)
				^ (std::hash<float>()(k._position.z) << 1);
		}
	};
}

/* Textures map to block type */
const std::map<BlockType, std::tuple<sf::Vector2f, sf::Vector2f, sf::Vector2f> > textureMap = {
	{	BlockType::Air,      { sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0) }	},
	{	BlockType::Dirt,     { sf::Vector2f(2, 0), sf::Vector2f(2, 0), sf::Vector2f(2, 0) }	},
	{	BlockType::Grass,    { sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(2, 0) }	},
	{	BlockType::Stone,    { sf::Vector2f(3, 0), sf::Vector2f(3, 0), sf::Vector2f(3, 0) }	}
};


