#pragma once

/*
* Mesh only handle 2/3 of matrixs 
* View * Projection matrixs 
*/

struct Mesh {
	std::vector<GLfloat> vertexPositions; // 3
	std::vector<GLfloat> textureCoords;	  // 2
	std::vector<GLuint>  indices;		  // 
};