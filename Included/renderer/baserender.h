#pragma once

#include "glm.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Camera;
class BaseModel;
class QuadTexture;

class BaseRender 
{
public:
	virtual void RenderModels( Camera*, QuadTexture*) = 0;
	virtual void AddModel( BaseModel* ) = 0;
	virtual std::vector< BaseModel* > 
		GetRenderModels() = 0;

	virtual void RenderModelsByListLocation(
		Camera*,
		BaseModel*,
		QuadTexture*,
		std::vector<sf::Vector3f> &
	) = 0;
};

