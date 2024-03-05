#pragma once
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <memory>

struct Context {
	~Context() { delete m_pWindow; }
	Context() {

		/* make window context */
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 3;
		settings.minorVersion = 0;

		/* create window and setting  */
		m_width = 1000;
		m_height = 1000;
		m_pWindow = new sf::Window(sf::VideoMode(m_width, m_height), "OpenGL", sf::Style::Default, settings);
		m_pWindow->setVerticalSyncEnabled(true);
		m_pWindow->setActive(true);
		m_pWindow->setFramerateLimit(60);

		/* load glad */
		if (!gladLoadGL()) {
			exit(-1);
		}

		glViewport(0, 0, m_pWindow->getSize().x, m_pWindow->getSize().y);
		glCullFace(GL_BACK);		/* setting not display faces at the back */
		glEnable(GL_DEPTH_TEST);	/* enable z-buffer */

	};

	int m_width;
	int m_height;
	sf::Window*  m_pWindow;
};

