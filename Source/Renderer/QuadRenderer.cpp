#include "renderer/quadrenderer.h"
#include "entity/camera.h"
#include "shader/BasicShader.h"
#include "basemodel.h"
#include "world/quad/quadmodel.h"
#include "texture/QuadTexture.h"
#include "ultils/matrix.h"
#include <iostream>


QuadRender::QuadRender() 
	: _defaultShader(new BasicShader("Quad","Quad"))
{ }

QuadRender::~QuadRender() {
	if (_defaultShader) {
		delete _defaultShader;
		_defaultShader = NULL;
	}
}

std::vector< sf::Vector3f > QuadRender::GetLocation() {
	return _quadLocations;
};

void QuadRender::AddNewLocation(sf::Vector3f l ) {
	_quadLocations.push_back(l);
};

void QuadRender::RenderModels(Camera* c , QuadModel* m) {

	/* activate sahder , vao and texture */
	_defaultShader->Activate();
	m->GetVao().bind();
	m->GetTexture()->bind();

	/* binding shader */
	c->UpdateCameraVector();

	/* model view projection */
	_defaultShader->LoadViewMatrix(c->GetViewMatrix());
	_defaultShader->LoadProjectionMatrix(c->GetProjectionMatrix());

	for (auto& quad : GetLocation() ) {

		_defaultShader->LoadModelMatrix(MakeModelMatrix(ConvertToGlmVec3f(quad), glm::vec3{0,0,0}));

		// draw using indices 
		glDrawElements(GL_TRIANGLES, GLsizei(m->GetIndiceCount()), GL_UNSIGNED_INT, 0);
	}

	m->GetTexture()->unbind();
	
};