#include "Application.h"
#include "Context.h"
#include "Mesh.h"

#include <SFML/Window.hpp>
#include <iostream>


Application::Application() 
{
	_running = true;

	if (_pContext == NULL) { _pContext = new Context(); }

	if (_pEngine == NULL) { _pEngine = new Engine(_pContext, this ); }
}

Application::~Application() {

	if (_pEngine != NULL) { delete _pEngine;}

	if (_pContext != NULL) { delete _pContext;}
}

void Application::RunLoop() {

	sf::Clock clock;

	/* Init Game Engine */
	_pEngine->InitGame();

	while (_running) {
		
		sf::Event event;

		sf::Time time = clock.restart();

		float startTime = time.asSeconds();

		while (_pContext->_pWindow->pollEvent(event))
		{
			if ((time.asSeconds() - startTime) >= (1 / 60)) {

				HandleEvents( event ); // application event 

				_pEngine->UpdateGameLogic(
					event,
					time.asSeconds() - startTime
				);

				startTime = time.asSeconds();

			}

		}
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw OpenGL level 
		_pEngine->Draw();

		// sfml window display buffer
		_pContext->_pWindow->display();

	}
}

void Application::TurnOffMouse() { _pContext->_pWindow->setMouseCursorVisible(false); }

void Application::TurnOnMouse() { _pContext->_pWindow->setMouseCursorVisible(true); }

void Application::CenteringMousePosition() {
	sf::Mouse::setPosition(
		sf::Vector2i(_pContext->_width / 2, _pContext->_height / 2),
		*_pContext->_pWindow);
}

void Application::HandleEvents(sf::Event& e) {

	/*
	* handle event at application level
	*/

	switch (e.type)
	{
	case sf::Event::Closed:

		_pContext->_pWindow->close();

		_running = false;

		break;

	case sf::Event::KeyPressed:

		switch (e.key.code)
		{
		case sf::Keyboard::Escape:

			_running = false;

			_pContext->_pWindow->close();

			break;

		default:

			break;
		}
	case sf::Event::Resized:
		// should handle at engine level 
		// adjust the viewport when the window is resized
		glViewport(0, 0, e.size.width, e.size.height);

	default:

		break;
	}
}


