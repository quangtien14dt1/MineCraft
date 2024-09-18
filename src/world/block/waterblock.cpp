#include "world/block/blockcontribute.h"


Block* WaterBlock::operator()()
{
	return this;
};

WaterBlock::WaterBlock()
{
	texTopCoords = sf::Vector2i(8, 0);
	texSideCoords = sf::Vector2i(8, 0);
	texBottomCoords = sf::Vector2i(8, 0);
}
