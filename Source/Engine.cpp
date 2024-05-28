#include <SFML/Window.hpp>
#include <exception>
#include <iostream>
#include <memory.h>

#include "Engine.h"
#include "../Entity/Camera.h"
#include "../KeyBoard.h"
#include "../Shader/BasicShader.h"
#include "Entity/ModelLoading.h"
#include "Entity/Mesh.h"
#include "../Texture/Texture.h"
#include "../KeyBoard.h"
#include "../Entity/Model.h"
#include "../Entity/Cube.h"



/*
	model -> view -> projection -> viewport transform
*/

void Engine::ErrorMessage(const char* c)
{
	/*MessageBoxA(NULL, c, "error", MB_ICONERROR);*/
}


Engine::Engine(  Config* cf,  Application* a, Context* ct)
{
	_pConfig = cf;
	_pContext = ct;
	_pApplication = a;
	_shader = new BasicShader("Cube", "Cube");
	_camera = new Camera( _pConfig, _pContext );
	Attach(_camera);
}

Engine::~Engine() {
	if (_shader != NULL ) { delete _shader; _shader = nullptr; }
	if (_camera != NULL)  { delete _camera; _camera = nullptr; }
};

int Engine::InitGame() {

	auto ptr = std::make_shared<Cube>();
	ptr->InitModel();
	AddNewData(ptr);

	return 1;

};

void Engine::UpdateGameLogic(sf::Event& e,float d) {

	/* 
	* Handle Event from engine level 
	* Notify for all Observer intance 
	* to update and handle event
	*/
	Notify(e, d);
	/* Shader unifitions */
};

void Engine::Draw() {

	std::for_each(_vModel.begin(), _vModel.end(), [this](std::shared_ptr<Model>& p) {
		p->DrawModel(*_shader, *_camera);
	});
};

Camera* Engine::GetCamera() { return _camera; };

void Engine::AddNewData( const std::shared_ptr< Model > m ) {  _vModel.push_back(m);  };

int Engine::RemoveData() { return 1; }

void Engine::Attach(IObserver* observer) { _observer.push_back(observer); };

void Engine::Detach(IObserver* observer) { _observer.remove(observer); };

void Engine::Notify(sf::Event& e, float del) {
	std::list<IObserver*>::iterator iterator = _observer.begin();
	
	while (iterator != _observer.end()) {
		(*iterator)->Update(e, del);
		++iterator;
	}
};
