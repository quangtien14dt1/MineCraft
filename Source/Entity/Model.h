#pragma once

#include "../glm.h"

class Mesh;

class Model {
public:

	Model() = default;
	/* abstrct functions */
	virtual void InitModel() = 0;
	virtual void addData(const Mesh& mesh) = 0;
	virtual void deleteData() = 0;
	virtual void addVBO(int dimensions, const std::vector<GLfloat>& data) = 0;
	virtual void bindVAO() = 0;
	virtual void addEBO(const std::vector<GLuint>& indices) = 0;

};