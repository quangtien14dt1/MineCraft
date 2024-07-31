#include "renderer/CubeRenderer.h"
#include "entity/Camera.h"
#include "world/block/BlockDatabase.h"
#include "world/block/BlockContribute.h"
#include "shader/BasicShader.h"
#include "Model.h"
#include <vector>
#include <iostream>


CubeRenderer::CubeRenderer( ) {

	_cubeShader = new BasicShader("Cube", "Cube");

};

CubeRenderer::~CubeRenderer() { 
	if (_cubeShader != NULL) {
		delete _cubeShader; _cubeShader = nullptr;
	}
};

void CubeRenderer::create(const Block& b ) { };

void CubeRenderer::add(const glm::vec3& position) { }

void CubeRenderer::render( Camera* camera, bool poly ) {
	
	// std::pair<Block*, Model*> >
	std::vector< Block* > blocks 
		= BlockDatabase::GetInstance()->GetAllBlocks();
		
	for (auto& block :  blocks) {

		/* recalculate texture coordinates and update  */
		std::vector<GLfloat> texCoords =
			BlockDatabase::GetInstance()->GetTextureCoords(block);

		BlockDatabase::GetInstance()->GetModel()->UpdateVBOTextureCoord(
			texCoords
		);

		/* activate shader , bind vao and texture */ 
		_cubeShader->Activate();
		BlockDatabase::GetInstance()->GetModel()->GetVao().bind();
		BlockDatabase::GetInstance()->GetTexture()->bind();

		/* update camera */
		camera->UpdateCameraVector();

		/* project view model */
		_cubeShader->LoadViewMatrix(camera->GetViewMatrix());
		_cubeShader->LoadProjectionMatrix(camera->GetProjectionMatrix());

		const glm::vec3 location{block->location.x, block->location.y, block->location.z};
		_cubeShader->LoadModelMatrix(
			BlockDatabase::GetInstance()->GetModel()->ModelMatrix(
				location,
				DEFAULT_ROTATION
			)
		);

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

}

void CubeRenderer::RenderBySection(const std::vector<Block*>& blocks) {

};


