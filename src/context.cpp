
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include "Context.h"


void SetupConfig(Config& cf) {
	cf._width = 1500;
	cf._height = 1500;
	cf._angle = 90.0f;
	cf._close = 0.1f;
	cf._far = 10000.0f;
};

void SetupWindowContext(Config& cf, Context& c) {

	/* make window context */
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	/* create window and setting  */
	c._width = cf._width;
	c._height = cf._height;
	c._pWindow = new sf::Window(
		sf::VideoMode(c._width, c._height), "OpenGL", sf::Style::Fullscreen, settings);
	c._pWindow->setVerticalSyncEnabled(true);
	c._pWindow->setActive(true);
	c._pWindow->setFramerateLimit(60);

	if (!gladLoadGL()) {exit(-1);}

	glViewport(0, 0, c._pWindow->getSize().x, c._pWindow->getSize().y);
	glEnable(GL_DEPTH_TEST);	/* enable z-buffer */
	glEnable(GL_CULL_FACE);		/* enable culling face */
	glCullFace(GL_BACK);		/* setting not display faces at the back */	
	glFrontFace(GL_CCW);		/* */

};


