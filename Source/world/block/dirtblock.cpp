#include "world/block/blockcontribute.h"


Block* DirtBlock::operator()()
{
	texTopCoords = sf::Vector2f(2, 0);
	texSideCoords = sf::Vector2f(2, 0);
	texBottomCoords = sf::Vector2f(2, 0);

	return this;
};
