#include "world/chunk/chunkmesh.h"

ChunkMesh::ChunkMesh() {}

void ChunkMesh::AddFace(
	 const std::vector<GLfloat>& blockFace,
	 const std::vector<GLfloat>& textureCoords,
	 const sf::Vector3i& chunkPosition,
	 const sf::Vector3i& blockPosition ) 
{

}

const Model& ChunkMesh::GetModel() const {
	return _model;
}