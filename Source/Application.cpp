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

	sf::Clock clock;

	/* Init Game Engine */
	//m_pEngine->InitGame();

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

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

		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// end the current frame (internally swaps the front and back buffers)
		m_pContext->m_pWindow->display();

		////m_pContext->m_pWindow->setActive(true);
		////
		////sf::Time time = clock.restart();
		////float startTime = time.asSeconds();

		//m_pContext->m_pWindow->setVerticalSyncEnabled(true);
		//m_pContext->m_pWindow->setActive();
		//
		//while (m_pContext->m_pWindow->isOpen()) {

		//	//GLfloat vertices[] =
		//	//{
		//	//	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		//	//	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		//	//	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		//	//	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		//	//	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		//	//	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
		//	//};

		//	//// Indices for vertices order
		//	//GLuint indices[] =
		//	//{
		//	//	0, 3, 5, // Lower left triangle
		//	//	3, 2, 4, // Lower right triangle
		//	//	5, 4, 1 // Upper triangle
		//	//};

		//	//BasicShader s = BasicShader("Default", "Default");
		//	//Camera c = Camera(m_pContext, 45, 0.1f, 100.0f);

		//	//VAO VAO1;
		//	//VAO1.Bind();

		//	//VBO VBO1(vertices, sizeof(vertices));
		//	//EBO EBO1(indices, sizeof(indices));

		//	//VAO1.LinkVBO(VBO1, 0);

		//	//VAO1.Unbind();
		//	//VBO1.Unbind();
		//	//EBO1.Unbind();

		//	//if ( ( time.asSeconds() - startTime) >= ( 1/60) ) {

		//	//	/*m_pEngine->UpdateGameLogic(time.asSeconds() - startTime);

		//	//	m_pEngine->Draw();*/

		//	//	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//	//	glClear(GL_COLOR_BUFFER_BIT);

		//	//	//m.Draw(s, c);

		//	//	s.Activate();

		//	//	VAO1.Bind();

		//	//	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//	//	startTime = time.asSeconds();
		//	//}

		//	// clear buffer 
		//	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//	//glClear(GL_COLOR_BUFFER_BIT);

		//	//// draw
		//	//s.Activate();
		//	//VAO1.Bind();
		//	//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//	m_pContext->m_pWindow->clear();
		//	m_pContext->m_pWindow->draw(shape);
		//	m_pContext->m_pWindow->display();

		//	// display
		//	m_pContext->m_pWindow->display();

		//	/* handle event at application level */
		//	HandleEvents();

		//	//std::cout << 1.f / time.asSeconds() << "\n";
		//}

		//m_pContext->m_pWindow->close();

		//m_bRunning = false;
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

