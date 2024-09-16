#include "renderer/modelsrender.h"
#include "entity/camera.h"
#include "world/block/blockcontribute.h"
#include "shader/basicShader.h"
#include "world/block/blockmodel.h"
#include "texture/quadtexture.h"
#include "texture/cubetexture.h"
#include "ultils/matrix.h"
#include <vector>
#include <iostream>


ModelRender::ModelRender( )
	:_defaultShader( new BasicShader("Cube", "Cube"))
{ };

ModelRender::~ModelRender() {

	for (auto& m : _modelList) {

		delete m;

	}

	_modelList.clear();

	if (_defaultShader != NULL) {
		delete _defaultShader; 
		_defaultShader = nullptr;
	}
};

std::vector< BaseModel* > 
ModelRender::GetRenderModels() {
	return _modelList;
};

void ModelRender::AddNewLocation(sf::Vector3f l) { 
	_modelLocations.push_back(l);
}

std::vector< sf::Vector3f > 
ModelRender::GetLocation() {
	return _modelLocations;
};

void ModelRender::SetRenderMode(bool m) { _polyMode = m; };

void ModelRender::AddModel( BaseModel* m) {
	_modelList.push_back(m);
}

void ModelRender::RenderModels( Camera* c, QuadTexture* t) {

	for (auto& m : _modelList) {
		/* activate shader , bind vao and texture */
		_defaultShader->Activate();
		m->GetVao().bind();
		t->bind();

		/* update camera */
		c->UpdateCameraVector();

		/* project view model */
		_defaultShader->LoadViewMatrix(c->GetViewMatrix());
		_defaultShader->LoadProjectionMatrix(c->GetProjectionMatrix());
		_defaultShader->LoadModelMatrix(
			MakeModelMatrix(
				ConvertToGlmVec3f(m->GetModelLocation()),
				DEFAULT_ROTATION)
		);

		/* draw model by indices */
		glDrawElements(
			GL_TRIANGLES,
			m->GetIndiceCount(),
			GL_UNSIGNED_INT, 0
		);

		Polygon();

	}

}

void ModelRender::RenderModelsByListLocation(
	Camera* c,
	BaseModel* m,
	QuadTexture* t,
	std::vector<sf::Vector3f>& locations
)
{
	/* activate shader , bind vao and texture */
	_defaultShader->Activate();
	m->GetVao().bind();
	t->bind();

	/* update camera */
	c->UpdateCameraVector();

	/* project view model */
	_defaultShader->LoadViewMatrix(c->GetViewMatrix());
	_defaultShader->LoadProjectionMatrix(c->GetProjectionMatrix());

	for (auto& l : locations) {

		_defaultShader->LoadModelMatrix(
			MakeModelMatrix(ConvertToGlmVec3f(l), DEFAULT_ROTATION));

#ifdef LAB
		/* draw line only */
		glDrawElements(
			GL_TRIANGLES,
			m->GetIndiceCount(),
			GL_UNSIGNED_INT, 0
		);

		Polygon();

		/* draw by strip triangle */
		//glDrawElements(GL_TRIANGLE_STRIP, GLsizei(pair.second->getIndiceCount()), GL_UNSIGNED_INT, 0);

#else
		/* draw using indices */
		glDrawElements(GL_TRIANGLES, GLsizei(pair.second->getIndiceCount()), GL_UNSIGNED_INT, 0);

		Polygon();

#endif // LAB
	}
};


const void ModelRender::Polygon() const  {
	if (_polyMode) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
}
;


