#include "CubeRenderer.h"
#include "../Entity/Camera.h"
#include "../World/Block/BlockDatabase.h"
#include "../World/Block/BlockContribute.h"
#include "../Shader/BasicShader.h"
#include "../Entity/Model.h"
#include <vector>
#include <iostream>


CubeRenderer::CubeRenderer( ) {

	std::cout << "Init Cube Renderer..." << std::endl;

	std::cout << "Init cube shader program..." << std::endl;
	_cubeShader = new BasicShader("Cube", "Cube");

};

CubeRenderer::~CubeRenderer() { 
	if (_cubeShader != NULL) {
		delete _cubeShader; _cubeShader = nullptr;
	}
};

void CubeRenderer::create(const Block& b ) { };

void CubeRenderer::add(const glm::vec3& position) { }

void CubeRenderer::render( Camera* camera ) {
	

	std::vector< std::pair<Block*, Model*> > data =
		BlockDatabase::GetInstance()->GetAllBlocks();


	for (auto& pair : data) {
		/* activate shader , bind vao and texture */
		_cubeShader->Activate();
		pair.second->getVao().bind();
		BlockDatabase::GetInstance()->GetTexture()->bind();

		/* update camera */
		camera->UpdateCameraVector();

		/* project view model */
		_cubeShader->LoadViewMatrix(camera->GetViewMatrix());
		_cubeShader->LoadProjectionMatrix(camera->GetProjectionMatrix());
		_cubeShader->LoadModelMatrix(
			pair.second->modelMatrix( pair.first->cubeLocation, pair.first->cubeRotation )
		);

		
		
#ifdef LAB
		/* draw line only */
		glDrawElements(GL_TRIANGLES, GLsizei(pair.second->getIndiceCount()), GL_UNSIGNED_INT, 0);

		/* draw by strip triangle */
		//glDrawElements(GL_TRIANGLE_STRIP, GLsizei(pair.second->getIndiceCount()), GL_UNSIGNED_INT, 0);

#else
		/* draw using indices */
		glDrawElements(GL_TRIANGLES, GLsizei(pair.second->getIndiceCount()), GL_UNSIGNED_INT, 0);

#endif // LAB

		

		

	}

}


