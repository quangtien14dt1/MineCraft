#include "world/block/blockcontribute.h"


Block* AirBlock::operator()()
{
	texTopCoords = sf::Vector2f(0, 0);
	texSideCoords = sf::Vector2f(0, 0);
	texBottomCoords = sf::Vector2f(0, 0);

	return this;
};
