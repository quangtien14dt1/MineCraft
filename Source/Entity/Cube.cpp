#include "Cube.h"
#include "../glm.h"

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
		Vertex{ glm::vec3(-1.0f, -1.0f,  1.0f)}, //        7--------6	| Y
		Vertex{ glm::vec3( 1.0f, -1.0f,  1.0f)}, //       /|       /|	| |
		Vertex{ glm::vec3( 1.0f, -1.0f, -1.0f)}, //      4--------5 |	| |_________
		Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f)}, //      | |      | |	| |			|
		Vertex{ glm::vec3(-1.0f,  1.0f,  1.0f)}, //	     | 3------|-2	| |			| 
		Vertex{ glm::vec3( 1.0f,  1.0f,  1.0f)}, //      |/       |/	| |			|
		Vertex{ glm::vec3( 1.0f,  1.0f, -1.0f)}, //      0--------1		| |_________|_______X
		Vertex{ glm::vec3(-1.0f,  1.0f, -1.0f)} //
	};

	/*Texture textures[]
	{
		Texture("container")
	};*/

	/*_tex = std::vector<Texture>(
		textures, textures + sizeof(textures) / sizeof(Texture)
	);*/
	//_tex.push_back(Texture("container"));

	_mesh = Mesh(
		std::vector<Vertex>(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex)),
		std::vector<GLuint>(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint) ),
		this
	);
}

void Cube::SetModelLocation(glm::vec3 v) { _position = v; };

glm::vec3 Cube::GetModelLocation() { return _position; };

void Cube::SetDefaultLocation() { }; // default position 0

glm::mat4 Cube::GetModelMatrix() { return _defModel; };

void Cube::TranslateModel() { _defModel = glm::translate(_defModel, _position); };

void Cube::RotateModel(float a) { _defModel = glm::rotate(_defModel, glm::radians(a), _position); };

void Cube::DrawModel(BasicShader& s, Camera& c) { _mesh.DrawMesh(s, c); };