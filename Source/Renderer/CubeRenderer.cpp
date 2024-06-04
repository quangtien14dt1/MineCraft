#include "CubeRenderer.h"
#include <vector>


CubeRenderer::CubeRenderer() : m_cubeTexture("DefaultPack") {

	std::vector<GLuint> indices
	{
		// back
		0, 1, 2,
		2, 3, 0,

		// front
		4, 5, 6,
		6, 7, 4,

		// right 
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,

		// top 
		16, 17, 18,
		18, 19, 16,

		// bottom
		20, 21, 22,
		22, 23, 20
	};

	std::vector<GLfloat> vertexCoords
	{
		// back
		1, 0, 0, //        7--------6	| Y
		0, 0, 0, //       /|       /|	| |
		0, 1, 0, //      4--------5 |	| |_________
		1, 1, 0, //      | |      | |	| |			|
				 //	     | 3------|-2	| |			| 
				 //	     |/       |/	| |			|
		// front //	     |/       |/	| |			|
		1, 0, 1, //      0--------1		| |_________|_______X
		1, 0, 1, //      
		1, 1, 1, //
		0, 1, 1,

		// right
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		// left
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		// top
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		// bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1.
	};

	auto top = m_cubeTexture.GetTexture({0,0});
	auto side = m_cubeTexture.GetTexture({1,0});
	auto bottom = m_cubeTexture.GetTexture({2,0});

	std::vector<GLfloat> texCoords;
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), top.begin(), side.end());
	texCoords.insert(texCoords.end(), bottom.begin(), side.end());

	m_cubeModel.addData({ vertexCoords, texCoords, indices });
};

void CubeRenderer::add(const glm::vec3& position) { 
	m_cubes.push_back(position);
}

void CubeRenderer::render(const Camera& camera) {


}

