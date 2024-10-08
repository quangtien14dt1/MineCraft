#pragma once

#include <SFML/Graphics.hpp>
#include "modelloading.h"
#include "glm.h"
#include "Mesh.h"


class BaseModel {

public:

	~BaseModel();

	/* abstrct functions */
	virtual void InitModel( );
	virtual void AddData( const Mesh& );
	virtual void DeleteData( );
	virtual void AddEBO(const std::vector<GLuint>&);
	virtual VAO	 GetVao( );
	virtual void AddVBO( 
		GLuint , 
		const std::vector<GLfloat>& 
	);

	virtual void UpdateVBOTextureCoord( 
		std::vector<GLfloat>& );

	GLuint GetIndiceCount( ) const;

	/* it own model's location */
	sf::Vector3f GetModelLocation();
	void SetModelLocation( sf::Vector3f);

private:
	
	sf::Vector3f		_defaultLocation;
	VAO					m_vao;
	GLuint				m_vboCount = 0; 
	GLuint				m_indicesCount = 0;
	std::vector<VBO> m_buffers;

};
