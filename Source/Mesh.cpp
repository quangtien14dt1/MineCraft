#include "Mesh.h"
#include "glm.h"
#include <iostream>


glm::mat4 Mesh::DefaultModel() {

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);
	return objectModel;
}


Mesh::Mesh() 
{
    //this->m_vertices = v;
    //this->m_indices  = i;
    //this->m_textures = t;

	//float vertices[] = {
	// 0.5f,  0.5f, 0.0f,  // top right
	// 0.5f, -0.5f, 0.0f,  // bottom right
	//-0.5f, -0.5f, 0.0f,  // bottom left
	//-0.5f,  0.5f, 0.0f   // top left 
	//};
	//unsigned int indices[] = {  // note that we start from 0!
	//	0, 1, 3,   // first triangle
	//	1, 2, 3    // second triangle
	//};

	Vertex vertices[] = {
		Vertex{	glm::vec3(-1.0f, 0.0f,  1.0f) },
		Vertex{	glm::vec3(-1.0f, 0.0f, -1.0f) },
		Vertex{	glm::vec3( 1.0f, 0.0f, -1.0f) },
		Vertex{	glm::vec3( 1.0f, 0.0f,  1.0f) }
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	m_vao.Bind();

	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));

	VBO vbo(verts); // buffer in vbo 
	EBO ebo(inds);

	/* know how (VAO) to use buffer  */
	m_vao.LinkVBO(vbo, 0);
	//m_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	//m_vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//m_vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	m_vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
};

void Mesh::AsString() {

};

Mesh::~Mesh() { };


//void Mesh::Draw(BasicShader& s, Camera& c)
void Mesh::Draw() {
	//s.Activate();
	m_vao.Bind();

	//// load texture 
	//m_textures[0].TextureUnit(s, "texture1", 0);
	//m_textures[0].BindTexture();

	//s.LoadViewMatrix( c.GetViewMatrix() );					// view 
	//s.LoadProjectionMatrix( c.GetProjectionMatrix() );		// projection
	//s.LoadModelMatrix(DefaultModel());						// model

	// indices
	//DrawMeshIndices();

	// saving m_cameraMatrix for changing glsl later
	//m_cameraMatrix = c.GetProjectionViewMatrix();

};

void Mesh::DrawMeshIndices() {

	//GLuint size = GLuint(this->m_indices.size());
	//glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

}

