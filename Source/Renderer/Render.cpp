#include "Render.h"
#include "../World/Block/BlockDatabase.h"
#include <iostream>


void Render::render(Camera* c)  {

	//_quadRenderer->render(c);
	_cubeRenderer->render(c);

};

void Render::DatabaseBinding(BlockDatabase* p) {
};

Render::Render()
{ 
	std::cout << "Init Quad renderer..." << std::endl;
	_quadRenderer = new QuadRenderer();

	std::cout << "Init Cube renderer..." << std::endl;
	_cubeRenderer = new CubeRenderer();

};

Render::~Render() { 

	if (_quadRenderer != NULL) {
		delete _quadRenderer; _quadRenderer = nullptr;
	}

	if (_cubeRenderer != NULL) {
		delete _cubeRenderer; _cubeRenderer = nullptr;
	}
};

