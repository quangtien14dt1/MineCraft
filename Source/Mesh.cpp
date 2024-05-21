#include "glm.h"
#include "Mesh.h"
#include "Shader/BasicShader.h"
#include "texture/Texture.h"
#include "../ModelLoading.h"
#include "../Entity/Camera.h"
#include "../KeyBoard.h"

#include <iostream>


void Mesh::MeshInit(
		std::vector <Vertex> v
		, std::vector <GLuint> i 
		//,std::vector <Texture> t 
) {

	this->_vertices = v;
	this->_indices  = i;
	//this->_textures = t;

	_vao.Bind();

	VBO vbo(this->_vertices);
	EBO ebo(this->_indices);

	/* know how (VAO) to use buffer  */
	_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	_vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	/* Unbind all to prevent accidentally modifying them */
	_vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
};

void Mesh::AsString() { };

Mesh::~Mesh() { };

void Mesh::DrawMesh(BasicShader& s, Camera& c) {
	s.Activate();
	_vao.Bind();

	//_textures[0].TextureUnit(s, "cubeTexture", 0);
	//_textures[0].BindTexture();

	c.UpdateCameraVector();
	s.LoadModelMatrix(_defPosition);
	s.LoadViewMatrix(c.GetViewMatrix());
	s.LoadProjectionMatrix(c.GetProjectionMatrix());
	
	// draw using indices 
	glDrawElements(GL_TRIANGLES, GLsizei(_indices.size()), GL_UNSIGNED_INT, 0);

	// draw using triagle
	//glDrawArrays(GL_TRIANGLES, 0, 36);
};

glm::mat4 Mesh::DefaultModel() { return glm::mat4(); }






