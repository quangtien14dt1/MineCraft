#include "QuadRenderer.h"
#include "../Entity/Camera.h"
#include <iostream>


QuadRenderer::QuadRenderer() {

	m_texture.LoadFromFile("test");
	m_quadModel.AddData({
		{
			/* vertex coord */
			-0.5,  0.5, 0,
			 0.5,  0.5, 0,
			 0.5, -0.5, 0,
			-0.5, -0.5, 0,
		},
		{
			/* texture coords */
			0, 1,
			1, 1,
			1, 0,
			0, 0,
		},
		{
			/* indices */
			0, 1, 2,
			2, 3, 0
		}
	});

	m_shader = BasicShader("Quad", "Quad");
};

void QuadRenderer::add(const glm::vec3& position) {
	m_quads.push_back(position);
};

void QuadRenderer::render(Camera* camera) {

	/* activate sahder , vao and texture */
	m_shader.Activate();
	m_quadModel.GetVao().bind();
	m_texture.bind();

	/* binding shader */
	camera->UpdateCameraVector();
	m_shader.LoadViewMatrix(camera->GetViewMatrix());
	m_shader.LoadProjectionMatrix(camera->GetProjectionMatrix());

	for (auto& quad : m_quads) {

		m_shader.LoadModelMatrix(m_quadModel.ModelMatrix( quad,glm::vec3{0,0,0} ));

		// draw using indices 
		glDrawElements(GL_TRIANGLES, GLsizei(m_quadModel.GetIndiceCount()), GL_UNSIGNED_INT, 0);
	}
	m_texture.unbind();
	
};