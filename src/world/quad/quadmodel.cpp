#include "world/quad/quadmodel.h"
#include "texture/QuadTexture.h"

QuadModel::QuadModel(QuadTexture* texture)
	:_quadTexture(texture)
{
	CreateQuadMesh();
}

void QuadModel::CreateQuadMesh( ) {

	std::vector<GLfloat> vertexCoords{
		/* vertex coord */
		-0.5,  0.5, 0,
		 0.5,  0.5, 0,
		 0.5, -0.5, 0,
		-0.5, -0.5, 0,
	};

	std::vector<GLfloat> texCoords{
		/* texture coords */
		0, 1,
		1, 1,
		1, 0,
		0, 0,
	};

	std::vector<GLuint> indices {
		/* indices */
		0, 1, 2,
		2, 3, 0
	};

	_mesh.vertexPositions = vertexCoords;
	_mesh.textureCoords = texCoords;
	_mesh.indices = indices;

	AddMeshToModel();

};

void QuadModel::AddMeshToModel() {
	AddData(_mesh);
};

QuadTexture* QuadModel::GetTexture() {
	return _quadTexture;
};

BaseModel* QuadModel::GetModel() {
	return dynamic_cast<BaseModel*>(this);
}