#include "world/chunk/chunkmodel.h"
#include "world/block/blockcontribute.h"
#include "world/worldcontant.h"
#include "mesh.h"


ChunkModel::ChunkModel()
{}

ChunkModel::~ChunkModel()
{}

/*
*/
void ChunkModel::AddFace(
	const std::vector<GLfloat>& face,
	const std::vector<GLfloat>& textureCoords,
	const sf::Vector3i& bl,
	const sf::Vector3i& cl 
)
{
	auto& verticies = _mesh.vertexPositions;
	auto& texCoords = _mesh.textureCoords;
	auto& indices	= _mesh.indices;

	/* add textures face coords */
	texCoords.insert(
					texCoords.end(), 
					textureCoords.begin(), 
					textureCoords.end()
	);

	/* 
	 vertices 
	*/
	for (int i = 0, index = 0; i < 4; ++i) {

		// first chessmap scale -> block location -> vertex
		verticies.push_back( cl.x * CHUNK_SIZE + bl.x + face[index++]);
		verticies.push_back( cl.y * CHUNK_SIZE + bl.y + face[index++]);
		verticies.push_back( cl.z * CHUNK_SIZE + bl.z + face[index++]);
	
	}

	/* indices */

	// back
	// 0, 1, 2,
	// 2, 3, 0,
	indices.insert(indices.end(), {
		_indexIndice , 
		_indexIndice + 1,
		_indexIndice + 2,
		_indexIndice + 2, 
		_indexIndice + 3, 
		_indexIndice
		});

	_indexIndice += 4;
}

void ChunkModel::AddMeshToModel() {
	AddData(_mesh);

	_mesh.vertexPositions.clear();
	_mesh.textureCoords.clear();
	_mesh.indices.clear();

	_mesh.vertexPositions.shrink_to_fit();
	_mesh.textureCoords.shrink_to_fit();
	_mesh.indices.shrink_to_fit();

	_indexIndice = 0;

};

BaseModel* ChunkModel::GetModel() {
	return dynamic_cast<BaseModel*>(this);
}