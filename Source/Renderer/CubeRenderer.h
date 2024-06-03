#pragma once

#include "../glm.h"
#include "../Entity/CubeModel.h"
#include "../Shader/Shader.h"
#include "../Texture/CubeTexture.h"
#include <vector>

class Camera;

class CubeRenderer
{
public:
	CubeRenderer() = default;

	void add(const glm::vec3& postion);

	void render(const Camera& camera);

private:

	std::vector<glm::vec3> m_cubes;

	CubeModel		m_cubeModel;
	BasicShader m_basicShader;
	CubeTexture m_cubeTexture;

};

