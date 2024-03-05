#include "Application.h"
#include "Mesh.h"
#include <iostream>


Application::Application() 
{
	_running = true;

	if (m_pContext == NULL) { m_pContext = new Context(); }

	if (m_pEngine == NULL) { m_pEngine = new Engine(m_pContext, this ); }
}

Application::~Application() {

	if (m_pEngine != NULL) { delete m_pEngine;}

	if (m_pContext != NULL) { delete m_pContext;}
}

void Application::RunLoop() {

	sf::Clock clock;

	/* Init Game Engine */
	m_pEngine->InitGame();

	while (_running) {
		
		sf::Event event;

		sf::Time time = clock.restart();

		float startTime = time.asSeconds();

		while (m_pContext->m_pWindow->pollEvent(event))
		{
			if ((time.asSeconds() - startTime) >= (1 / 60)) {

				HandleEvents( event ); // application event 

			}

		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...
		//m.Draw(s);
		m_pEngine->Draw();

		// end the current frame (internally swaps the front and back buffers)
		m_pContext->m_pWindow->display();

	}
}

void Application::TurnOffMouse() { m_pContext->m_pWindow->setMouseCursorVisible(false); }

void Application::TurnOnMouse() { m_pContext->m_pWindow->setMouseCursorVisible(true); }

void Application::CenteringMousePosition() {
	sf::Mouse::setPosition(
		sf::Vector2i(m_pContext->m_width / 2, m_pContext->m_height / 2),
		*m_pContext->m_pWindow);
}

void Application::HandleEvents(sf::Event& e) {

	/*
	* handle event at application level
	*/

	switch (e.type)
	{
	case sf::Event::Closed:

		m_pContext->m_pWindow->close();

		_running = false;

		break;

	case sf::Event::KeyPressed:

		switch (e.key.code)
		{
		case sf::Keyboard::Escape:

			_running = false;

			m_pContext->m_pWindow->close();

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


