#include "Application.h"
#include <iostream>


Application::Application() 
{
	if (m_pContext == NULL) { m_pContext = new Context(); }
	if (m_pEngine == NULL) { m_pEngine = new Engine(m_pContext, this ); }
}

Application::~Application() {
	if (m_pEngine != NULL) { delete m_pEngine;}
	if (m_pContext != NULL) { delete m_pContext;}
}

void Application::RunLoop() {

	m_bRunning = true;
	sf::Clock clock;

	/* Init Game Engine */
	m_pEngine->InitGame();
	
	while (m_bRunning) {
		
		sf::Time time = clock.restart();
		float startTime = time.asSeconds();
		
		while (m_pContext->m_pWindow->isOpen()) {

			if ( ( time.asSeconds() - startTime) >= ( 1/60) ) {

				m_pEngine->UpdateGameLogic(time.asSeconds() - startTime);

				m_pEngine->Draw();

				startTime = time.asSeconds();
			}

			// display
			m_pContext->m_pWindow->display();

			/* handle event at application level */
			HandleEvents();

			//std::cout << 1.f / time.asSeconds() << "\n";
		}

		m_pContext->m_pWindow->close();

		m_bRunning = false;
	}
}

void Application::HandleEvents() {
	sf::Event e; /* output event e */
	// handle event for engine layer

	/*
	* handle event at application level 
	*/
	while (m_pContext->m_pWindow->pollEvent(e)) {
		switch (e.type)
		{
		case sf::Event::Closed:
			m_pContext->m_pWindow->close();
			m_bRunning = false;
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code )
			{
			case sf::Keyboard::Escape:
				m_pContext->m_pWindow->close();
				m_bRunning = false;
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
}

void Application::TurnOffMouse() { m_pContext->m_pWindow->setMouseCursorVisible(false); }

void Application::TurnOnMouse() { m_pContext->m_pWindow->setMouseCursorVisible(true);  }

void Application::CenteringMousePosition() {
	sf::Mouse::setPosition(
		sf::Vector2i(m_pContext->m_width / 2, m_pContext->m_height / 2),
		*m_pContext->m_pWindow);
}
