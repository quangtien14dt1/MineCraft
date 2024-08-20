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

class ModelRender : public BaseRender {

public:
	ModelRender();
	~ModelRender();
	void RenderModels(Camera*, BaseModel*) override;
	void RenderModelsByListLocation(
		Camera*,
		BaseModel*,
		std::vector<sf::Vector3f>&
	) override;

	std::vector< const BaseModel* >
		GetRenderModels() override;

	std::vector< sf::Vector3f > GetLocation();
	void AddNewLocation(sf::Vector3f);
	void AddModel(const BaseModel*);
	void SetRenderMode(bool m);

	const void Polygon() const;
	
private:
	std::vector<sf::Vector3f > _modelLocations;
	std::vector< const BaseModel* >  _modelList;
	BasicShader* _defaultShader;
	bool _polyMode;
};


