#pragma once

#include "../glm.h"
#include <array>
#include <vector>

#include "glm.h"
#include "baserender.h"
#include <vector>

class BlockModel;
class BaseModel;
class Camera;
class BasicShader;

class CubeRender : public BaseRender {

public:
	CubeRender();
	~CubeRender();
	void RenderModels(Camera*, BlockModel*);
	std::vector< sf::Vector3f > GetLocation();
	void AddNewLocation(sf::Vector3f);

private:
	std::vector<sf::Vector3f > _cubeLocations;
	BasicShader* _defaultShader;
};


