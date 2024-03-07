#pragma once
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <memory>

struct Context {
	~Context() { delete _pWindow; }
	Context() {

		/* make window context */
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 3;
		settings.minorVersion = 0;

		/* create window and setting  */
		_width = 600;
		_height = 600;
		_pWindow = new sf::Window(sf::VideoMode(_width, _height), "OpenGL", sf::Style::Default, settings);
		_pWindow->setVerticalSyncEnabled(true);
		_pWindow->setActive(true);
		_pWindow->setFramerateLimit(60);

		/* load glad */
		if (!gladLoadGL()) {
			exit(-1);
		}

		glViewport(0, 0, _pWindow->getSize().x, _pWindow->getSize().y);
		glCullFace(GL_BACK);		/* setting not display faces at the back */
		glEnable(GL_DEPTH_TEST);	/* enable z-buffer */

	};

	int _width;
	int _height;
	sf::Window*  _pWindow;
};

