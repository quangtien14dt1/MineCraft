
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "Context.h"


Context::~Context() { delete _pWindow; }

Context::Context() {

		/* make window context */

		sf::ContextSettings settings;

		settings.depthBits = 24;

		settings.stencilBits = 8;

		settings.antialiasingLevel = 4;

		settings.majorVersion = 3;

		settings.minorVersion = 0;

		/* create window and setting  */
		_width = 1000;

		_height = 1000;

		_pWindow = new sf::Window(sf::VideoMode(_width, _height), "OpenGL", sf::Style::Default, settings);

		_pWindow->setVerticalSyncEnabled(true);

		_pWindow->setActive(true);

		_pWindow->setFramerateLimit(60);

		if (!gladLoadGL()) {

			exit(-1);
		}

		glViewport(0, 0, _pWindow->getSize().x, _pWindow->getSize().y);

		glCullFace(GL_BACK);		/* setting not display faces at the back */

		glEnable(GL_DEPTH_TEST);	/* enable z-buffer */

	};


