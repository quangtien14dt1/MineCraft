#include "CubeRenderer.h"


CubeRenderer::CubeRenderer() : m_cubeTexture("DefaultPack") {

};

void CubeRenderer::add(const glm::vec3& position) { 

	m_cubes.push_back(position);

}

void CubeRenderer::render(const Camera& camera) {
	glEnable(GL_CULL_FACE);

	m_basicShader.Activate();

}

