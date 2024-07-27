#include "CubeRenderer.h"
#include "../Entity/Camera.h"
#include "../World/Block/BlockDatabase.h"
#include "../World/Block/BlockContribute.h"
#include "../Shader/BasicShader.h"
#include "../Entity/Model.h"
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
	std::vector< Block* > blocks =
		BlockDatabase::GetInstance()->GetAllBlocks();


	for (auto& block : blocks) {

		/* update cube model texture */
		std::vector<GLfloat> texCoords = 
			BlockDatabase::GetInstance()->GetTextureCoords(block);

		BlockDatabase::GetInstance()->GetModel()->updateVBOTextureCoord(
			texCoords
		);

		/* activate shader , bind vao and texture */
		_cubeShader->Activate();
		BlockDatabase::GetInstance()->GetModel()->getVao().bind();
		BlockDatabase::GetInstance()->GetTexture()->bind();

		/* update camera */
		camera->UpdateCameraVector();

		/* project view model */
		_cubeShader->LoadViewMatrix(camera->GetViewMatrix());
		_cubeShader->LoadProjectionMatrix(camera->GetProjectionMatrix());
		_cubeShader->LoadModelMatrix(
			BlockDatabase::GetInstance()->GetModel()->modelMatrix ( 
				block->cubeLocation, 
				block->cubeRotation 
			)
		);

#ifdef LAB
		/* draw line only */
		glDrawElements( 
			GL_TRIANGLES, 
			GLsizei(
				BlockDatabase::GetInstance()->GetModel()->getIndiceCount()), 
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


