#include "Mesh.h"
#include "glm.h"
#include <iostream>


glm::mat4 Mesh::DefaultModel() {

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);
	return objectModel;
}


Mesh::Mesh( std::vector <Vertex> v,
            std::vector <GLuint> i
            //std::vector <Texture> t
) 
{
    this->m_vertices = v;
    this->m_indices  = i;
    //this->m_textures = t;

	SetupMesh();
};

void Mesh::AsString() {

};

Mesh::~Mesh() { };

void Mesh::Draw(BasicShader& s, Camera&c) {

	std::cout << "Draw Mesh" << std::endl;
	s.Activate();
	m_vao.Bind();

	//// load texture 
	//m_textures[0].TextureUnit(s, "texture1", 0);
	//m_textures[0].BindTexture();

	s.LoadViewMatrix( c.GetViewMatrix() );					// view 
	s.LoadProjectionMatrix( c.GetProjectionMatrix() );		// projection
	s.LoadModelMatrix(DefaultModel());						// model

	// indices
	DrawMeshIndices();

	// saving m_cameraMatrix for changing glsl later
	m_cameraMatrix = c.GetProjectionViewMatrix();

};

void Mesh::DrawMeshIndices() {

	glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);

}


/*
*	basiclly we create new array buffer VBO 
*	we also adding AVO to GPU know how to using VBO
*	
*/
void Mesh::SetupMesh( ) {

	m_vao.Bind();

	VBO vbo(this->m_vertices); // buffer in vbo 
	EBO ebo(this->m_indices);  // buffer in ebo

	/* know how (VAO) to use buffer  */
	m_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	m_vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	m_vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	m_vao.Unbind();

};