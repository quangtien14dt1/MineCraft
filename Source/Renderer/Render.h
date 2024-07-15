#pragma once
#include "../glm.h"
#include "QuadRenderer.h"
#include "CubeRenderer.h"

class Camera;
class BlockDatabase;

class Render 
{
public:

	Render( );

	void DatabaseBinding(BlockDatabase * p );

	void render(Camera* );
	~Render();

private:
	QuadRenderer* _quadRenderer;
	CubeRenderer* _cubeRenderer;
};

