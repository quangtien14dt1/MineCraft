#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include "glm.h"

static const glm::vec3 DEFAULT_ROTATION{ 0,0,0 };
static const glm::vec3 DEFAULT_LOCATION{ 0,0,0 };

class Chunk;

using Block_t = uint8_t;

enum class BlockType : Block_t {
	Air = 0,
	Grass = 1,
	Dirt = 2,
	Stone = 3,

	NUM_TYPES
};

class  Block {
public:
	/* cube textures coords */
	sf::Vector2f texTopCoords;
	sf::Vector2f texSideCoords;
	sf::Vector2f texBottomCoords;

	virtual Block* operator()() = 0;

};

class AirBlock : public Block {
public:
	AirBlock();
	Block* operator()() override;
};

class DirtBlock : public Block {
public:
	DirtBlock();
	Block* operator()() override;
};

class GrassBlock : public Block {
public:
	GrassBlock();
	Block* operator()() override;
};

class StoneBlock : public Block {
public:
	StoneBlock();
	Block* operator()() override;
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


