#include "Application.h"
#include "Mesh.h"
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

	sf::Clock clock;

	/* Init Game Engine */
	//m_pEngine->InitGame();

	Mesh m = Mesh();

	BasicShader s = BasicShader("Default", "Default");
	
	bool running = true;

	while (running) {
		// handle events
		sf::Event event;
		while (m_pContext->m_pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...
		s.Activate();

		m.Draw();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code )
			{
			case sf::Keyboard::Escape:
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
}

