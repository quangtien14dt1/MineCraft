#pragma once

#include "../glm.h"
#include "../Entity/CubeModel.h"
#include "../Shader/BasicShader.h"
#include "../Texture/Texture.h"
#include <vector>

class Camera;

class QuadRenderer
{
public:
	QuadRenderer();
	
	void add(const glm::vec3& position);

	void render(Camera& camera);

private:
	std::vector<glm::vec3> m_quads;

	CubeModel m_quadModel;
	BasicShader m_shader;
	Texture m_texture;
};

