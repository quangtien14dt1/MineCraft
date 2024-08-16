#pragma once

#include "glm.h"
#include "baserender.h"
#include <SFML/Graphics.hpp>
#include <vector>

class QuadModel;
class BaseModel;
class Camera;
class BasicShader;

class QuadRender : public BaseRender {

public:
	QuadRender();
	~QuadRender();
	void RenderModels(Camera*, QuadModel* );
	std::vector< sf::Vector3f > GetLocation();
	void AddNewLocation(sf::Vector3f);

private:
	std::vector<sf::Vector3f > _quadLocations;
	BasicShader* _defaultShader;
};

