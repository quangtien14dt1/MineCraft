#include "Render.h"
#include "../World/Block/BlockDatabase.h"
#include <iostream>


Render::Render()
	: _poligonRender(false)
{
	_quadRenderer = new QuadRenderer();
	_cubeRenderer = new CubeRenderer();
};

void 
Render::render(Camera* c, bool polygon )  { 
	_cubeRenderer->render(c, polygon); 
};

void 
Render::PolygonRenderMode(bool mode ) { _poligonRender = mode; };

bool Render::GetRenderMode() { return _poligonRender; };

void Render::DatabaseBinding(BlockDatabase* p) { };

Render::~Render() { 

	if ( _quadRenderer ) {
		delete _quadRenderer; 
		_quadRenderer = nullptr;
	}

	if ( _cubeRenderer ) {
		delete _cubeRenderer; 
		_cubeRenderer = nullptr;
	}
};

