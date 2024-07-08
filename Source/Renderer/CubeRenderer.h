#pragma once

#include "../glm.h"
#include "../Entity/Model.h"
#include "../Shader/Shader.h"
#include "../Texture/CubeTexture.h"
#include <vector>

class Camera;

class CubeRenderer
{
public:
	CubeRenderer();
	~CubeRenderer();

	void add(const glm::vec3& postion);

	void render( Camera* camera);

private:

	std::vector<glm::vec3> m_cubes;

	Model		m_cubeModel;
	BasicShader m_cubeShader;
	CubeTexture* _cubeTexture;

};

