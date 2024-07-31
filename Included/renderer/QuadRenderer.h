#pragma once

#include "glm.h"
#include "Model.h"
#include "shader/BasicShader.h"
#include "texture/QuadTexture.h"
#include <vector>

class Camera;

class QuadRenderer
{
public:
	QuadRenderer();
	
	void add(const glm::vec3& position);

	void render(Camera* camera);

private:
	std::vector<glm::vec3> m_quads;

	Model m_quadModel;
	BasicShader m_shader;
	QuadTexture m_texture;
};

