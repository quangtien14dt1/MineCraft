#pragma once

#include "glm.h"
#include <vector>

class Camera;
class BaseModel;

class BaseRender 
{
public:
	BaseRender();
	virtual void RenderModels( Camera*, bool ) = 0;
	virtual ~BaseRender( );
	virtual void AddModel( const BaseModel* ) = 0;
	virtual bool GetRenderModels() = 0;
private:
	std::vector<const BaseModel*> _model;
};

