#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Keyboard {
public:
	Keyboard();
	void update(sf::Event);
	bool isKeyDown(sf::Keyboard::Key key) const { return _keys[key]; };
	bool keyReleased(sf::Keyboard::Key key) const { return _recentReleased == key; };
private:
	std::array<bool, sf::Keyboard::KeyCount> _keys;
	sf::Keyboard::Key _recentReleased;
};