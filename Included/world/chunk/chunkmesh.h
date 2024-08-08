#pragma once

#include <SFML/Graphics.hpp>
#include "mesh.h"
#include "model.h"

class ChunkMesh
{
public:
	ChunkMesh();
	
	void AddFace(
		 const std::vector<GLfloat>& blockFace,
		 const std::vector<GLfloat>& textureCoords,
		 const Block* chunkPosition,
		 const sf::Vector3i& blockPosition
	);

	void BufferMesh();

	const Model& GetModel() const;
private:
	Mesh _mesh;
	Model _model;

};