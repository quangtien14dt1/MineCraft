#pragma once

#include "../glm.h"

class Model {

public:
	Model();
	virtual ~Model() = 0;
	virtual void UpdatePosition( const glm::vec3 ) = 0;
	virtual void GetPosition() const = 0;
private:

	glm::vec3 _position;

};