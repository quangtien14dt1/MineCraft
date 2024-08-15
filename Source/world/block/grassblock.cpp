#include "world/block/blockcontribute.h"


Block* GrassBlock::operator()()
{
	texTopCoords = sf::Vector2f(0, 0);
	texSideCoords = sf::Vector2f(1, 0);
	texBottomCoords = sf::Vector2f(2, 0);

	return this;
};
