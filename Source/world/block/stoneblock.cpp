#include "world/block/blockcontribute.h"

Block* StoneBlock::operator()()
{
	return this;
};

StoneBlock::StoneBlock()
{
	texTopCoords = sf::Vector2f(3, 0);
	texSideCoords = sf::Vector2f(3, 0);
	texBottomCoords = sf::Vector2f(3, 0);
}