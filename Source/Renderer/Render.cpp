#include "Render.h"


void Render::render(Camera* c)  {
	_quadRenderer->render(c);
	_cubeRenderer->render(c);
};

Render::Render()
{ 
	_quadRenderer = new QuadRenderer();
	_cubeRenderer = new CubeRenderer();

	//addQuad({0,0,0});
	addCube({0,0,0});
};

Render::~Render() { 
	delete _quadRenderer; 
	delete _cubeRenderer;
};

void Render::addQuad(const glm::vec3& pos) { _quadRenderer->add(pos); };

void Render::addCube(const glm::vec3& pos) { _cubeRenderer->add(pos); };
