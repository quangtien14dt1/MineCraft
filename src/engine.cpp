#include <SFML/Window.hpp>
#include <exception>
#include <iostream>
#include <glad/glad.h>
#include <memory.h>

#include "engine.h"
#include "entity/camera.h"
#include "modelloading.h"
#include "mesh.h"
#include "basemodel.h"
#include "renderer/baserender.h"
#include "renderer/modelsrender.h"
#include "shader/basicshader.h"
#include "world/block/blockdatabase.h"
#include "world/block/blockfactory.h"
#include "world/chunk/chunk.h"
#include "world/quad/quadmodel.h"
#include "world/chunk/chunkmodel.h"
#include "world/chunk/chunkmodelbuilder.h"
#include "world/block/blockmodel.h"
#include "texture/quadtexture.h"
#include "texture/cubetexture.h"
#include "world/world.h"




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
	: _polyMode(false)
{
	_pConfig = cf;
	_pContext = ct;
	_pApplication = a;

	/* with block instance camera and Rendermaster */
	_camera = new Camera( _pConfig, _pContext );

	_renderMaster = new ModelRender();

	_blockFactory = new BlockFactory();

	_chunkModelBuilder = new ChunkModelBuilder();

	_world = new World();

	Attach(_camera);

}

Engine::~Engine() {
	if (_camera != NULL)  { 
		delete _camera; _camera = nullptr; 
	}

	if (_renderMaster != NULL) { 
		delete _renderMaster; _renderMaster = nullptr; 
	}

	if (_chunkModelBuilder != NULL) {
		delete _chunkModelBuilder; _chunkModelBuilder = nullptr;
	}

	if (_world != NULL) {
		delete _world; _world = nullptr;
	}

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

void Engine::InitTexture() {
	
};

/**/
void Engine::LoadMap() {

	InitTexture();

	/* need baking chunk and chunk database ? */

	/* moving all logic to world class */

	_world->createChunkMap();

	_world->buildChunkMapModel(_chunkModelBuilder,_renderMaster );

};


void Engine::Invoke() {

	_world->WorldRender(_renderMaster, _camera);

};

void Engine::SetRenderMode( bool m ) { 

	_renderMaster->SetRenderMode(m);
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
