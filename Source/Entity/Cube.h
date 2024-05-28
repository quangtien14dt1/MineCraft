#pragma once

#include "ModelLoading.h"
#include "../Texture/Texture.h"
#include "Mesh.h"
#include "Model.h"


class Cube : public Model {

public:

	/* abstrct functions */
	void InitModel();
	void SetModelLocation(glm::vec3);
	void DrawModel(BasicShader&, Camera&);
	glm::mat4 GetModelMatrix();

	glm::vec3 GetModelLocation();
	void SetDefaultLocation(); 

	/* manipulate with model itself */
	void TranslateModel();
	void RotateModel(float);
	
	glm::vec3 _position;
	glm::mat4 _defModel = glm::mat4(1.0f);

private:

	Mesh _mesh;			// Mesh data

};
