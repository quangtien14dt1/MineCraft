#include "../glm.h"
#include "Mesh.h"
#include "ModelLoading.h"
#include "../Shader/BasicShader.h"
#include "../texture/Texture.h"
#include "../Entity/Camera.h"
#include "../KeyBoard.h"
#include "../Entity/Cube.h"
#include "../Entity/Model.h"

#include <iostream>


std::vector<Vertex> _vertices;
std::vector<GLuint> _indices;

// Using passing by value 
Mesh::Mesh( std::vector <Vertex> v,std::vector <GLuint> i ,Model* p) 
	: _vertices(v), _indices(i), _model(p)
{

	/* convert to using vertices and texture 
	 * should be using cube map 
	*/
	_vao.Bind();
	VBO vbo(this->_vertices);
	EBO ebo(this->_indices);

	/* know how (VAO) to use buffer  */
	_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	//_vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	/* Unbind all 
	   to prevent accidentally modifying them 
	*/
	_vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
};

void Mesh::AsString() {
	//std::cout << "View    : " << glm::to_string(_viewDirection) << std::endl;
	//std::cout << "Right   : " << glm::to_string(_right) << std::endl;
	//std::cout << "Up      : " << glm::to_string(_upPosition) << std::endl;
	//std::cout << "Position: " << glm::to_string(_position) << std::endl;
	//std::cout << "-----------------------------------------------------" << std::endl;
};

Mesh::~Mesh() { };

void Mesh::DrawMesh(BasicShader& s, Camera& c) {
	s.Activate();
	_vao.Bind();

	//_textures[0].TextureUnit(s, "cubeTexture", 0);
	//_textures[0].BindTexture();


	/* apply variable from camera */
	c.UpdateCameraVector();
	s.LoadModelMatrix(_model->GetModelMatrix());
	s.LoadViewMatrix(c.GetViewMatrix());
	s.LoadProjectionMatrix(c.GetProjectionMatrix());
	
	/* this look stupid , 
	* we may change it with class Renderer for 
	* changing the ways we render ,also add new effect 
	*/
	// draw using indices 
	glDrawElements(GL_TRIANGLES, GLsizei(_indices.size()), GL_UNSIGNED_INT, 0);

	// draw using triagle
	// glDrawArrays(GL_TRIANGLES, 0, 36);
};

glm::mat4 Mesh::DefaultModel() { return glm::mat4(); }






