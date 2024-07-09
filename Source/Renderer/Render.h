#pragma once
#include "../glm.h"
#include "QuadRenderer.h"
#include "CubeRenderer.h"

class Camera;

class Render 
{
public:

	Render();
	~Render();

	void addQuad(const glm::vec3& pos);
	void addCube(const glm::vec3& pos);

	void render(Camera* );
private:
	QuadRenderer* _quadRenderer{nullptr};
	CubeRenderer* _cubeRenderer{nullptr};

};

