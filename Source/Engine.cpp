#include <SFML/Window.hpp>
#include <exception>
#include <iostream>

#include "Engine.h"
#include "../Entity/Camera.h"
#include "../KeyBoard.h"
#include "../Shader/BasicShader.h"
#include "../ModelLoading.h"
#include "../Mesh.h"
#include "../Texture/Texture.h"
#include "../KeyBoard.h"


void Engine::ErrorMessage(const char* c)
{
	/*MessageBoxA(NULL, c, "error", MB_ICONERROR);*/
}


Engine::Engine(  Context* ct,  Application* a)
{
	_pContext = ct;

	_pApplication = a;

	_shader = new BasicShader("Default", "Default");

	_camera = new  Camera(ct, 90, 0.1f, 100.0f); 


}

Engine::~Engine() {

	 delete _camera; _camera = nullptr; 
	 delete _shader; _shader = nullptr; 

} ;

int Engine::InitGame() {

	Vertex vers[] = {
		//			COORDINATE				 //		TEXT COORDIMATES 				
		Vertex{ glm::vec3(0.5f,  0.5f, 0.0f),	glm::vec2(1.0f, 1.0f)},
		Vertex{ glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec2(1.0f, 0.0f)},
		Vertex{ glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec2(0.0f, 0.0f)},
		Vertex{ glm::vec3(-0.5f,  0.5f, 0.0f),	glm::vec2(0.0f, 1.0f)}
	};
	
	GLuint indices[] = { 
		0, 1, 3,
		1, 2, 3
	};

	Texture textures[]
	{
		Texture("container")
	};

	std::vector <Vertex> verts(vers, vers + sizeof(vers) / sizeof(Vertex));

	std::vector <GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));

	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));


	Mesh m = Mesh(verts, inds, tex);

	AddNewData( m );

	return 1;

};


void Engine::UpdateGameLogic(sf::Event& e,float d) {

	/* 
	* Handle Event from engine level 
	* we can apply a different keyboard and mouse controller later 
	* from this handle event at engine level 
	*/
	switch (e.type) {

	case sf::Event::KeyPressed:
		HandleKeyboard(e, d);
		break;

	case sf::Event::MouseMoved:
		// HandleMouseMoving(e, d);
		break;

	case sf::Event::MouseWheelScrolled:
		 HandleScrolling(e);
		break;

	default:
		break;
	}

	/* Shader unifitions */
};

void Engine::HandleKeyboard(sf::Event& e, float d) {

	switch (e.key.code)
	{
	case sf::Keyboard::A:

		_camera->ProcessKeyboard(Camera_Movement::LEFT, d);

		break;

	case sf::Keyboard::W:

		_camera->ProcessKeyboard(Camera_Movement::FORWARD, d);

		break;

	case sf::Keyboard::S:

		_camera->ProcessKeyboard(Camera_Movement::BACKWARD, d);

		break;

	case sf::Keyboard::D:

		_camera->ProcessKeyboard(Camera_Movement::RIGHT, d);

		break;

	default:

		break;
	}

};

void Engine::HandleMouseMoving(sf::Event& e, float d) {

	float dx = float(e.mouseMove.x - _pContext->_pWindow->getSize().x);

	float dy = float(e.mouseMove.y - _pContext->_pWindow->getSize().y);

	_camera->MouseUpdate(dx, dy);

	sf::Mouse::setPosition(
		sf::Vector2i(
			_pContext->_pWindow->getSize().x / 2,
			_pContext->_pWindow->getSize().y / 2),
		*_pContext->_pWindow);
};

void Engine::HandleScrolling(sf::Event& e) {

	_camera->ProcessMouseScrolling(e);

}

void Engine::Draw() {

	for (auto m : _vMesh) {
		
		m.DrawMesh(*_shader, *_camera);

	}

};

void Engine::AddNewData(Mesh m) { 

	_vMesh.push_back(m); 

};

int Engine::RemoveData() { return 1; }




