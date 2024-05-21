#include "Cube.h"

/* default cube init */
void Cube::InitModel() {

	unsigned int cubeIndices[] =
	{
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3
	};

	Vertex cubeVertices[] =
	{
		//   Coordinates
		Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f),  glm::vec2(0.0f,0.0f)},//  
		Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f),  glm::vec2(1.0f,0.0f)},//  
		Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f),  glm::vec2(1.0f,1.0f)},//  
		Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f),  glm::vec2(0.0f,1.0f)},//  
		Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f),  glm::vec2(0.0f,0.0f)},//  
		Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f),  glm::vec2(1.0f,0.0f)},//  
		Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f),  glm::vec2(1.0f,1.0f)},//  
		Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f),  glm::vec2(0.0f,1.0f)} // 

		//        7--------6	| Y
		//       /|       /|	| |
		//      4--------5 |	| |_________
		//      | |      | |	| |			|
		//	    | 3------|-2	| |			| 
		//      |/       |/		| |			|
		//      0--------1		| |_________|_______X

	};

	/*Texture textures[]
	{
		Texture("container")
	};*/

	_verts = std::vector<Vertex>(
			cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex)
	);

	_inds = std::vector<GLuint>(
		cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint)
	);

	/*_tex = std::vector<Texture>(
		textures, textures + sizeof(textures) / sizeof(Texture)
	);*/
	//_tex.push_back(Texture("container"));

	_mesh.MeshInit(
		_verts, _inds
	);
}

void Cube::SetModelPosition(glm::vec3 v) {
	_position = v;
};

void Cube::DrawModel(BasicShader& s, Camera& c) { 
	_mesh.DrawMesh(s, c); 
};

void Cube::SetDefaultPosition() { }; // default position 0