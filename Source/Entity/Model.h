#pragma once

#include "../glm.h"

class BasicShader;
class Camera;

class Model {
public:
	virtual void InitModel() = 0;
	virtual void SetModelLocation(glm::vec3) = 0;
	virtual void DrawModel(BasicShader&, Camera&) = 0;
	virtual glm::mat4 GetModelMatrix() = 0;
};