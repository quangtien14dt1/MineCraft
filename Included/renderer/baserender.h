#pragma once

#include "glm.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Camera;
class BaseModel;

class BaseRender 
{
public:
	virtual void RenderModels( Camera*, BaseModel*) = 0;
	virtual void AddModel( const BaseModel* ) = 0;
	virtual std::vector< const BaseModel* > 
		GetRenderModels() = 0;

	virtual void RenderModelsByListLocation(
		Camera*,
		BaseModel*,
		std::vector<sf::Vector3f> &
	) = 0;
};

