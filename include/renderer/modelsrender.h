#pragma once

#include <array>
#include <vector>
#include <vector>
#include <SFML/Graphics.hpp>
#include "glm.h"
#include "baserender.h"


class BlockModel;
class BaseModel;
class Camera;
class BasicShader;
class QuadTexture;

class ModelRender : public BaseRender {

public:
	ModelRender();
	~ModelRender();
	void RenderModels(Camera*, QuadTexture*) override;
	void RenderModelsByListLocation(
		Camera*,
		BaseModel*,
		QuadTexture*,
		std::vector<sf::Vector3f>&
	) override;

	std::vector< BaseModel* >
		GetRenderModels() override;

	std::vector< sf::Vector3f > GetLocation();
	void AddNewLocation(sf::Vector3f);
	void AddModel( BaseModel*);
	void SetRenderMode(bool m);

	const void Polygon() const;
	
private:
	std::vector<sf::Vector3f > _modelLocations;
	std::vector< BaseModel* >  _modelList;
	BasicShader* _defaultShader;
	bool _polyMode;
};


