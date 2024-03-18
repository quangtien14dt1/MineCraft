#include "glm.h"
#include "Mesh.h"
#include "Shader/BasicShader.h"
#include "texture/Texture.h"
#include "../ModelLoading.h"
#include "../Entity/Camera.h"
#include "../KeyBoard.h"

#include <iostream>



Mesh::Mesh( std::vector <Vertex> v,std::vector <GLuint> i, std::vector <Texture> t ) {

	this->_vertices = v;

	this->_indices  = i;

	this->_textures = t;

	_vao.Bind();

	VBO vbo(this->_vertices);

	EBO ebo(this->_indices);

	/* know how (VAO) to use buffer  */
	_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);

	_vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	_vao.Unbind();

	vbo.Unbind();

	ebo.Unbind();
};

void Mesh::AsString() {

};

Mesh::~Mesh() { };

void Mesh::DrawMesh(BasicShader& s, Camera& c) {

	s.Activate();

	_vao.Bind();

	_textures[0].TextureUnit(s, "texture1", 0);

	_textures[0].BindTexture();

	glm::mat4 model = glm::mat4(1.0f);

	s.LoadModelMatrix(model);

	c.UniformMatrix(s);

	glDrawElements(GL_TRIANGLES, GLsizei(_indices.size()), GL_UNSIGNED_INT, 0);


};


glm::mat4 Mesh::DefaultModel() {

	glm::mat4 objectModel = glm::mat4(1.0f);

	glm::mat4 model = glm::mat4(1.0f);

	objectModel = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	return objectModel;

}






