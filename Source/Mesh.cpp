#include "glm.h"
#include "Mesh.h"
#include "Shader/BasicShader.h"
#include "texture/Texture.h"
#include "../ModelLoading.h"
#include "../Entity/Camera.h"

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

	_textures[0].TextureUnit(s, "texture", 0);
	_textures[0].BindTexture();

	glm::mat4 model = glm::mat4(1.0f); 
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.0f);

	s.LoadViewMatrix( view );

	s.LoadProjectionMatrix(projection);

	s.LoadModelMatrix(model);

	glDrawElements(GL_TRIANGLES, GLsizei(_indices.size()), GL_UNSIGNED_INT, 0);


};


glm::mat4 Mesh::DefaultModel() {

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, -0.50f);

	glm::mat4 objectModel = glm::mat4(1.0f);

	objectModel = glm::translate(objectModel, objectPos);

	return objectModel;
}






