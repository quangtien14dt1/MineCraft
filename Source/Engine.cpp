#include "Engine.h"
#include <SFML/Window.hpp>
#include <exception>
#include <iostream>

void Engine::ErrorMessage(const char* c)
{
	/*MessageBoxA(NULL, c, "error", MB_ICONERROR);*/
}


Engine::Engine(  Context* ct,  Application* a)
{
	m_pContext = ct;
	m_pApplication = a;
	m_shader = BasicShader("Default", "Default");
	m_camera = Camera(ct, 45, 0.1f, 100.0f); 
	m_keyboard = Keyboard();

}

Engine::~Engine() {
} ;

int Engine::InitGame() {

	std::cout << "Init game " << std::endl;
	//Vertex vertices[] =
	//{ //               COORDINATES           /            COLORS          /       TEXTURE COORDINATES    //
	//	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	//	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	//	Vertex{glm::vec3(1.0f, 0.0f, -1.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	//	Vertex{glm::vec3(1.0f, 0.0f,  1.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
	//};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	// textures
	Texture textures[]
	{
		Texture("aiuehara")
	};


	// store mesh data in vector 
	//std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	//std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	//std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	std::cout << "Init Mesh " << std::endl;
	// create Mesh model
	//Mesh m = Mesh(verts, ind);
	//AddNewData( m );

	return 1;

};


int Engine::UpdateGameLogic(float d) {

	/* 
	* Handle Event from engine level 
	* we can apply a different keyboard and mouse controller later 
	* from this handle event at engine level 
	*/
	sf::Event e;

	while (m_pContext->m_pWindow->pollEvent(e)) {

		switch (e.type) {

		case sf::Event::KeyPressed:
			HandleKeyboard(e, d);
			break;

		case sf::Event::MouseMoved:
			//HandleMouseMoving(e, d);
			break;

		case sf::Event::MouseWheelScrolled:
			HandleScrolling(e, d);
			break;

		default:
			break;
		}

	}


	/* Shader unifitions */

	
	return 1;

};

void Engine::Draw() {

	//// clear and import new background buffer color 
	//std::cout << "Clear buffer " << std::endl;
	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//for (auto m : m_vMesh) {
	//	
	//	m.Draw(m_shader, m_camera);
	//}

	//m_pContext->m_pWindow->display();
};

//void Engine::AddNewData(Mesh& m) { 
//	//std::cout << "Add Mesh " << std::endl;
//	//m_vMesh.push_back(m); 
//
//};

int Engine::RemoveData() { return 1; }

void Engine::HandleKeyboard(sf::Event& e, float d) {
	std::cout << "Handle keyboard" << std::endl;
	switch (e.key.code)
	{
	case sf::Keyboard::A:
		m_camera.MoveLeft(d);
		break;
	case sf::Keyboard::W:
		m_camera.MoveFront(d);
		break;
	case sf::Keyboard::S:
		m_camera.MoveBack(d);
		break;
	case sf::Keyboard::D:
		m_camera.MoveRight(d);
		break;
	default:
		break;
	}

};

void Engine::HandleMouseMoving(sf::Event& e, float d) {

	std::cout << "Handle keyboard" << std::endl;
	// getting delta movement
	float dx = e.mouseMove.x - m_pContext->m_pWindow->getSize().x;
	float dy = e.mouseMove.y - m_pContext->m_pWindow->getSize().y;

	// update camera 
	m_camera.MouseUpdate(dx, dy);

	// reset mouse position to center
	sf::Mouse::setPosition(
		sf::Vector2i(
			m_pContext->m_pWindow->getSize().x / 2,
			m_pContext->m_pWindow->getSize().y / 2),
		*m_pContext->m_pWindow);
};

void Engine::HandleScrolling(sf::Event& e, float d) {}
