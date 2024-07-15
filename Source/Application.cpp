#include "Application.h"
#include "Context.h"
#include "Engine.h"
#include "glm.h"
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <iostream>


Application::Application(std::string applicationName) {
	SetupConfig(_config);
	SetupWindowContext(_config, _context);
	_pEngine = new Engine(&_config, this , &_context); 

	_context._pWindow->setTitle(applicationName);
	_context._pWindow->setMouseCursorVisible(false);

	cursorDisplay = false;
	windowFocus = true;
	
}

Application::~Application() { if (_pEngine != NULL) { delete _pEngine;} }

void Application::RunLoop() {

	sf::Time holdTime = sf::Time::Zero;
	sf::Time runTime = sf::Time::Zero;
	sf::Time update = sf::seconds(0.01f / 60.f);

	sf::Event e;

	_pEngine->LoadMap();

	try{
		while (_context._pWindow->isOpen()) {

			runTime += _clock.restart();
			float deltaTime = runTime.asSeconds() - holdTime.asSeconds();
			if (deltaTime = update.asSeconds()) {
				/*
				* Centerlizing mouse cursor
				* Polling Event handle from SFML
				*/
				// CenteringMousePosition();
				while (_context._pWindow->pollEvent(e))
				{
					_pEngine->UpdateGameLogic(
						e,
						deltaTime
					);

				}
				
			}

			HandleEvents(e);

			//LockMouseInsideWindow();

			cleanBuffer();

			_pEngine->Invoke();

			_context._pWindow->display();

			holdTime = runTime;

		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
}

void Application::cleanBuffer()
{
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::CenteringMousePosition() {
	sf::Mouse::setPosition(
		sf::Vector2i(_context._width / 2, _context._height / 2),
		*_context._pWindow);
}

void Application::CursorFocusWindow(bool f) {
	_context._pWindow->setMouseCursorVisible(f);
}

bool Application::LockMouseInsideWindow() {

	if (windowFocus) {

		sf::Vector2i cursorPos = sf::Mouse::getPosition(*_context._pWindow);
		sf::Vector2u windowSize = _context._pWindow->getSize();
		/* out of x direction */
		if (cursorPos.x < 0) {
			sf::Mouse::setPosition(
				sf::Vector2i(0, cursorPos.y), *_context._pWindow
			);
		}
		else if (cursorPos.x >= static_cast<int>(windowSize.x)) {

			sf::Mouse::setPosition(
				sf::Vector2i(windowSize.x - 1, cursorPos.y), *_context._pWindow);
		}

		/* out of y direction */
		if (cursorPos.y < 0) {
			sf::Mouse::setPosition(
				sf::Vector2i(cursorPos.x, 0), *_context._pWindow
			);
		}
		else if (cursorPos.y >= static_cast<int>(windowSize.y)) {
			sf::Mouse::setPosition(sf::Vector2i(
				cursorPos.x, windowSize.y - 1), *_context._pWindow
			);
		}
	}
	
	

	return 1;
		
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

			/*_context._pWindow->close();*/
			windowFocus = false;
			_context._pWindow->setMouseCursorVisible(true);

			break;

		case sf::Event::GainedFocus:
			_context._pWindow->setMouseCursorVisible(false);
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


