#include "renderer/cubeRenderer.h"
#include "entity/camera.h"
#include "world/block/blockDatabase.h"
#include "world/block/blockContribute.h"
#include "shader/basicShader.h"
#include "model.h"
#include <vector>
#include <iostream>


CubeRenderer::CubeRenderer( ) {

	_cubeShader = new BasicShader("Cube", "Cube");
	_model = new Model();
};

CubeRenderer::~CubeRenderer() { 
	if (_cubeShader != NULL) {
		delete _cubeShader; _cubeShader = nullptr;
	}

	if (_model != NULL) {
		delete _model; _model = nullptr;
	}
};

void CubeRenderer::create(const Block& b ) { };

void CubeRenderer::add(const glm::vec3& position) { }

void CubeRenderer::render( Camera* camera, bool poly ) {
	
	// std::pair<Block*, Model*> >
	BlockDatabase::GetInstance()->CreateDefaultCubeModel(_model);


	/* activate shader , bind vao and texture */ 
	_cubeShader->Activate();
	_model->GetVao().bind();
	BlockDatabase::GetInstance()->GetTexture()->bind();

	/* update camera */
	camera->UpdateCameraVector();

	/* project view model */
	
	_cubeShader->LoadViewMatrix(camera->GetViewMatrix());
	_cubeShader->LoadProjectionMatrix(camera->GetProjectionMatrix());
	_cubeShader->LoadModelMatrix(_model->ModelMatrix( _default, DEFAULT_ROTATION ) );

#ifdef LAB
	/* draw line only */
	glDrawElements(
		GL_TRIANGLES,
		GLsizei(
			BlockDatabase::GetInstance()->GetModel()->GetIndiceCount()),
		GL_UNSIGNED_INT, 0
	);

	/* draw by strip triangle */
	//glDrawElements(GL_TRIANGLE_STRIP, GLsizei(pair.second->getIndiceCount()), GL_UNSIGNED_INT, 0);

#else
	/* draw using indices */
	glDrawElements(GL_TRIANGLES, GLsizei(pair.second->getIndiceCount()), GL_UNSIGNED_INT, 0);

#endif // LAB


}

void CubeRenderer::RenderBySection(const std::vector<Block*>& blocks) {

};


