#pragma once

#include "../glm.h"
#include "../Context.h"
#include "../Engine.h"
#include "../KeyBoard.h"


/* POV parameter  */
struct POVDATA {
	POVDATA() 
		: angle(0)
		, width(0)
		, height(0)
		, closePlane(0)
		, farPlane(0)
	{ /* do mothing */ }

	float	angle;

	int		width;

	int		height;

	float	closePlane;

	float	farPlane;
};


class BasicShader;

class Camera
{

public:

	Camera();
	/*
	* Context* 
	* Angle 
	* closePlane
	* farPlane
	*/
	Camera(const Context*,float,float,float);

	/* make project view model matrix */;
	glm::mat4 ViewMatrix();

	glm::mat4 ProjectionMatrix();

	void UniformMatrix(BasicShader& );

	void ProcessKeyboard(Camera_Movement , float );

	void MouseUpdate(const float&, const float&);

	void ProcessMouseScrolling(sf::Event&);

private:

	POVDATA _sProjectionData;

	sf::Window* _pWindow;

	void UpdateCameraVector();

public:

	glm::mat4 _viewMatrix = glm::mat4(1.0f);

	glm::mat4 _projectionMatrix = glm::mat4(1.0f);

	glm::vec3 _viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::vec3 _upPosition = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 3.0f);

	glm::vec3 _right;

	float _rSpeed{ 0.3f };		// sensitivity 

	float _speed{ 4.5f };

	float _yaw{ -90.0f };		// turn your head left and right

	float _pitch{ 0.0f };		// turn your head up and down 


};