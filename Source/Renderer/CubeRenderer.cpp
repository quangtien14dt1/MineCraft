#include "CubeRenderer.h"
#include "../Entity/Camera.h"
#include <vector>
#include <iostream>


CubeRenderer::CubeRenderer( ) {

	std::cout << "Init Cube Renderer..." << std::endl;

	std::cout << "Init cube shader program..." << std::endl;
	m_cubeShader = BasicShader("Cube", "Cube");

	std::cout << "Create cube image ..." << std::endl;
	_cubeTexture = new CubeTexture();

	_cubeTexture->SetupCubeImage("DefaultPack");


	std::vector<GLuint> indices
	{

		//        7--------6	| Y
		//       /|       /|	| |
		//      0--------1 |	| |_________
		//      | |      | |	| |			|
		//	    | 3------|-2	| |			| 
		//	    | /      | /	| |			|
		//	    |/       |/		| |			|
		//      3--------2		| |_________|_______X

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
		1, 0, 0, //0       2--------3	| Y
		0, 0, 0, //1      /|       /|	| |
		0, 1, 0, //2     7--------6 |	| 1_________1
		1, 1, 0, //3     | |      | |	| |		  / |
				 //      | 1------|-0	| |		/	| 
				 //	     | /      | /	| |	  /	    |
		// front //	     |/       |/	| |	/		|
		0, 0, 1, //4     4--------5		| 0_________1_______X
		1, 0, 1, //5     
		1, 1, 1, //6
		0, 1, 1, //7

		// right
		1, 0, 1, //8
		1, 0, 0, //9
		1, 1, 0, //10
		1, 1, 1, //11

		// left
		0, 0, 0, //12
		0, 0, 1, //13
		0, 1, 1, //14
		0, 1, 0, //15

		// top
		0, 1, 1, //16
		1, 1, 1, //17
		1, 1, 0, //18
		0, 1, 0, //19

		// bottom
		0, 0, 0, //20
		1, 0, 0, //21
		1, 0, 1, //22
		0, 0, 1 //23
	};

	auto top = _cubeTexture->GetTexture({0,0});
	auto side = _cubeTexture->GetTexture({1,0});
	auto bottom = _cubeTexture->GetTexture({2,0});

	std::vector<GLfloat> texCoords;
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), top.begin(), top.end());
	texCoords.insert(texCoords.end(), bottom.begin(), bottom.end());

	m_cubeModel.addData({ vertexCoords, texCoords, indices });

	

	
};
CubeRenderer::~CubeRenderer() { delete _cubeTexture; };


void CubeRenderer::add(const glm::vec3& position) { 
	m_cubes.push_back(position);
}

void CubeRenderer::render( Camera* camera ) {

	/* activate sahder , vao and texture */
	m_cubeShader.Activate();
	m_cubeModel.getVao().bind();
	_cubeTexture->bind();

	/* binding shader */
	camera->UpdateCameraVector();
	m_cubeShader.LoadViewMatrix(camera->GetViewMatrix());
	m_cubeShader.LoadProjectionMatrix(camera->GetProjectionMatrix());

	for (auto& cube : m_cubes) {

		m_cubeShader.LoadModelMatrix(m_cubeModel.modelMatrix(cube, glm::vec3{ 0,0,0 }));

		// draw using indices 
		glDrawElements(GL_TRIANGLES, GLsizei(m_cubeModel.getIndiceCount()), GL_UNSIGNED_INT, 0);
	}
}

