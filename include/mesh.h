#pragma once

struct Mesh {
	std::vector<GLfloat> vertexPositions; 
	std::vector<GLfloat> textureCoords;	  
	std::vector<GLuint>  indices;		  
};