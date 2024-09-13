#include "world/block/blockcontribute.h"


Block* DirtBlock::operator()()
{
	return this;
};

DirtBlock::DirtBlock()
{
	texTopCoords = sf::Vector2i(2, 0);
	texSideCoords = sf::Vector2i(2, 0);
	texBottomCoords = sf::Vector2i(2, 0);
}