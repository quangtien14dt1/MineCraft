#include "Application.h"
#include "Context.h"
#include "Mesh.h"
#include "Engine.h"
#include <SFML/Window.hpp>
#include <iostream>


Application::Application() {
	SetupConfig(_config);
	SetupWindowContext(_config, _context);
	_pEngine = new Engine(_config, this ); 
}

Application::~Application() { if (_pEngine != NULL) { delete _pEngine;} }

void Application::RunLoop() {

	sf::Time holdTime = sf::Time::Zero;
	sf::Time runTime = sf::Time::Zero;
	sf::Time update = sf::seconds(1.f / 60.f);

	/* Init Game Engine */
	_pEngine->InitGame();
	sf::Event e;
	while (_context._pWindow->isOpen()) {

		HandleEvents(e);

		runTime += _clock.restart();

		float deltaTime = runTime.asSeconds() - holdTime.asSeconds();

		if ( deltaTime > update.asSeconds()) {

			// std::cout << "time: " << deltaTime << std::endl;

			while (_context._pWindow->pollEvent(e))
			{

				_pEngine->UpdateGameLogic(
					e,
					deltaTime
				);

			}

		}

		// clear the buffers
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw OpenGL level 
		_pEngine->Draw();

		// sfml window display buffer
		_context._pWindow->display();

		holdTime = runTime;

	}
}

void Application::TurnOffMouse() { _context._pWindow->setMouseCursorVisible(false); }

void Application::TurnOnMouse() { _context._pWindow->setMouseCursorVisible(true); }

void Application::CenteringMousePosition() {
	sf::Mouse::setPosition(
		sf::Vector2i(_context._width / 2, _context._height / 2),
		*_context._pWindow);
}

void Application::HandleEvents(sf::Event& e) {

	/*
	* handle event at application level
	*/

	switch (e.type)
	{
	case sf::Event::Closed:

		_context._pWindow->close();

		break;

	case sf::Event::KeyPressed:

		switch (e.key.code)
		{
		case sf::Keyboard::Escape:

			_context._pWindow->close();

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


