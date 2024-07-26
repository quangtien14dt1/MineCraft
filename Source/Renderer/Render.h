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

	void render(Camera*, bool );

	~Render();

	void PolygonRenderMode( bool );
	bool GetRenderMode();

private:
	bool _poligonRender;

	QuadRenderer* _quadRenderer;
	CubeRenderer* _cubeRenderer;
};

