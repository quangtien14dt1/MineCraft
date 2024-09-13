#include "world/block/blockcontribute.h"

Block* StoneBlock::operator()()
{
	return this;
};

StoneBlock::StoneBlock()
{
	texTopCoords	= sf::Vector2i(3, 0);
	texSideCoords	= sf::Vector2i(3, 0);
	texBottomCoords = sf::Vector2i(3, 0);
}