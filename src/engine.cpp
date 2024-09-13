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

	_quadTexture = new QuadTexture();

	_cubeTexture = new CubeTexture();

	_blockFactory = new BlockFactory();

	Attach(_camera);

}

Engine::~Engine() {
	if (_camera != NULL)  { 
		delete _camera; _camera = nullptr; 
	}

	if (_renderMaster != NULL) { 
		delete _renderMaster; _renderMaster = nullptr; 
	}

	if (_quadTexture != NULL) {
		delete _quadTexture; _quadTexture = nullptr;
	}

	if (_cubeTexture != NULL) {
		delete _cubeTexture; _cubeTexture = nullptr;
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
	_quadTexture->LoadFromFile("test");
	_cubeTexture->SetupCubeImage("DefaultPack");
};

/**/
void Engine::LoadMap() {

	InitTexture();

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
	BlockModel model(_cubeTexture);

	Chunk chunk({0,0,0});

	chunk.BlocksConfiguration();

	ChunkModel* chunkModel = new ChunkModel();

	ChunkModelBuilder builder;

	builder.BuildMesh(*chunkModel, chunk, *_cubeTexture);

	_renderMaster->AddModel(chunkModel);
	 
};


void Engine::Invoke() {

	_renderMaster->RenderModels(_camera, _cubeTexture);
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
