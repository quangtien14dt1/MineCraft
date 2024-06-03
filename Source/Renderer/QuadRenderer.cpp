#include "QuadRenderer.h"
#include "../Entity/Camera.h"


QuadRenderer::QuadRenderer() {
	m_texture.LoadFromFile("test");
	m_quadModel.addData({
		{
			-0.5,  0.5, 0,
			 0.5,  0.5, 0,
			 0.5, -0.5, 0,
			-0.5, -0.5, 0,
		},
		{
			0, 1,
			1, 1,
			1, 0,
			0, 0,
		},
		{
			0, 1, 2,
			2, 3, 0
		}
	});

	m_shader = BasicShader("Cube", "Cube");
};

void QuadRenderer::add(const glm::vec3& position) {
	m_quads.push_back(position);
};

void QuadRenderer::render( Camera& camera) {
	if (m_quads.empty())  return;

	m_shader.Activate();
	m_quadModel.bindVAO();
	m_texture.BindTexture();

	camera.UpdateCameraVector();
	
	m_shader.LoadViewMatrix(camera.GetViewMatrix());
	m_shader.LoadProjectionMatrix(camera.GetProjectionMatrix());

	for (auto& quad : m_quads) {

		m_shader.LoadModelMatrix(m_quadModel.makeModelMatrix(quad));

		// draw using indices 
		glDrawElements(GL_TRIANGLES, GLsizei(m_quadModel.getIndiceCount()), GL_UNSIGNED_INT, 0);
	}
	
};