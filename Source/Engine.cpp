#include <SFML/Window.hpp>
#include <exception>
#include <iostream>
#include <glad/glad.h>
#include <memory.h>

#include "Engine.h"
#include "Entity/Camera.h"
#include "Entity/ModelLoading.h"
#include "Entity/Mesh.h"
#include "Entity/Model.h"
#include "Renderer/Render.h"
#include "../Shader/BasicShader.h"
#include "../World/Block/BlockDatabase.h"
#include "../World/Block/BlockFactory.h"
#include "../World/Chunk/Chunk.h"




/*
	model -> view -> projection -> viewport transform
*/

void Engine::ErrorMessage(const char* c)
{
	/*MessageBoxA(NULL, c, "error", MB_ICONERROR);*/
}

Engine* Engine::_pEngine = nullptr;

Engine* Engine::GetInstance(
	Config* cf, Application* a, Context* ct) {
	if (_pEngine == nullptr) {
		_pEngine = new Engine(cf,a,ct);
	}
	return _pEngine;
};

Engine::Engine(  Config* cf,  Application* a, Context* ct)
{
	_pConfig = cf;
	_pContext = ct;
	_pApplication = a;

	/* with block instance camera and Rendermaster */
	std::cout << "Init camera..." << std::endl;
	_camera = new Camera( _pConfig, _pContext );

	std::cout << "Init render master..." << std::endl;
	_renderMaster = new Render();

	//std::cout << "Init block database..." << std::endl;
	//_blockDatabase = new BlockDatabase();

	//std::cout << "Init block factory..." << std::endl;
	//_blockFactory = BlockFactory::GetInstance();

	//std::cout << "Binding database to renderer..." << std::endl;
	//_renderMaster->DatabaseBinding(_blockDatabase);

	/* attach intance that receive event queue  */
	Attach(_camera);

}

Engine::~Engine() {
	if (_camera != NULL)  { 
		delete _camera; _camera = nullptr; 
	}

	if (_renderMaster != NULL) { 
		delete _renderMaster; _renderMaster = nullptr; 
	}

	//if (_blockDatabase != NULL) {
	//	delete _blockDatabase; _blockDatabase = nullptr;
	//}
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

/**/
void Engine::LoadMap() {

	BlockDatabase::GetInstance()->CreateDefaultCubeModel();

	/* need baking chunk and chunk database ? */

	/*
	*	should containt 3 level 
	*	chess 1  => map / noice , let say 10x 10 
	*	chessMan => chunk  / 16x16x256 
	*	bugs => block level / 
	* -   -  -  -
	*   |  |  |  |
	* -  -  -   -
	*   |  |  |  |
	* -  -  -   -
	* 
	*/

	Chunk chunk;
	chunk.CreateChunk();
};

void Engine::Invoke() {


	_renderMaster->render(_camera);

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
