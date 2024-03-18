#pragma once

#include <SFML/Window.hpp>

struct Context {
	int _width;
	int _height;
	sf::Window* _pWindow;
};

struct Config {
	float _width;
	float _height;
	float _angle;
	float _close;
	float _far;
};

void SetupConfig(Config&);
void SetupWindowContext(Config&, Context&);

