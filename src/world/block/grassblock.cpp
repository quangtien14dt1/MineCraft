#include "world/block/blockcontribute.h"

Block* GrassBlock::operator()()
{
	return this;
};

GrassBlock::GrassBlock()
{
	texTopCoords = sf::Vector2i(0, 0);
	texSideCoords = sf::Vector2i(1, 0);
	texBottomCoords = sf::Vector2i(2, 0);
}