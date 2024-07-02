#include "QuadRenderer.h"
#include "../Entity/Camera.h"
#include <iostream>


QuadRenderer::QuadRenderer() {

	std::cout << "Init Quad Renderer..." << std::endl;
	m_texture.LoadFromFile("test");
	m_quadModel.addData({
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
	m_quadModel.getVao().bind();
	m_texture.bind();
	m_texture.TextureUnit(m_shader,"quadTexture", 0);

	/* binding shader */
	camera->UpdateCameraVector();
	m_shader.LoadViewMatrix(camera->GetViewMatrix());
	m_shader.LoadProjectionMatrix(camera->GetProjectionMatrix());

	for (auto& quad : m_quads) {

		m_shader.LoadModelMatrix(m_quadModel.modelMatrix( quad,glm::vec3{0,0,0} ));

		// draw using indices 
		glDrawElements(GL_TRIANGLES, GLsizei(m_quadModel.getIndiceCount()), GL_UNSIGNED_INT, 0);
	}
	
};