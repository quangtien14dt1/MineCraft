#pragma once

#include <SFML/Window.hpp>

class Context {

public:

	~Context();

	Context();

	int _width;

	int _height;

	sf::Window*  _pWindow;
};

