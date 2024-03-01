#include "KeyBoard.h"


Keyboard::Keyboard()
{
	std::fill(_keys.begin(), _keys.end(), false);
	_recentReleased = sf::Keyboard::KeyCount;
}

void Keyboard::update(sf::Event e) {
	_recentReleased = sf::Keyboard::KeyCount; /* total number of keyboard */
	switch (e.type)
	{
	case sf::Event::KeyReleased:
		_keys[e.key.code] = false;
		break;
	case sf::Event::KeyPressed:
		_recentReleased = e.key.code;
		_keys[e.key.code] = true;
	default:
		break;
	}
}