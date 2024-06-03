#pragma once

/*
* Mesh only handle 2/3 of matrixs 
* View * Projection matrixs 
*/

struct Mesh {
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> textureCoords;
	std::vector<GLuint>  indices;
};