#include "renderer/cuberenderer.h"
#include "entity/camera.h"
#include "world/block/blockContribute.h"
#include "shader/basicShader.h"
#include "world/block/blockmodel.h"
#include "ultils/matrix.h"
#include <vector>
#include <iostream>


CubeRender::CubeRender( )
	:_defaultShader( new BasicShader("Cube", "Cube"))
{ };

CubeRender::~CubeRender() {
	if (_defaultShader != NULL) {
		delete _defaultShader; 
		_defaultShader = nullptr;
	}

};

std::vector< sf::Vector3f > 
CubeRender::GetLocation() {
	return _cubeLocations;
};

void CubeRender::AddNewLocation( sf::Vector3f l ) { }

void CubeRender::RenderModels( Camera* c, BlockModel* m ) {

	/* activate shader , bind vao and texture */ 
	_defaultShader->Activate();
	m->GetVao().bind();

	/* update camera */
	c->UpdateCameraVector();

	/* project view model */
	_defaultShader->LoadViewMatrix(c->GetViewMatrix());
	_defaultShader->LoadProjectionMatrix(c->GetProjectionMatrix());

	for (auto& cube : GetLocation()) {

		_defaultShader->LoadModelMatrix( MakeModelMatrix(ConvertToGlmVec3f(cube), DEFAULT_ROTATION));

		#ifdef LAB
				/* draw line only */
				glDrawElements(
					GL_TRIANGLES,
					m->GetModel()->GetIndiceCount(),
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



