#pragma once

#include "../glm.h"
#include "../Context.h"


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


/*
* handle *View and *Projection Matrix4
*/
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
	Camera(const Context* ,float,float,float);

	/* make project view model matrix */
	glm::mat4 CamMatrix();

	void MoveUp(float );
	void MoveDown(float );
	void MoveLeft(float );
	void MoveRight(float );
	void MoveFront(float );
	void MoveBack(float );
	void MouseUpdate(const float&, const float&);

private:
	POVDATA _sProjectionData;
	sf::Window* _pWindow;

	/* saving matrix */
	glm::mat4 _camMatrix = glm::mat4(1.0f);

public:
	glm::vec3 _viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _upPositipon = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 _position;

	float _rSpeed{ 0.3f };		// yaw pitch roll sensitivity
	float _mSpeed{ 0.05f };		// moving sensitivity
	float _speed{ 5 };

	float _yaw{ 0.0f };			// turn your head left and right
	float _pitch{ 0.0f };		// turn your head up and down 
	//float m_roll;				// not using , rotate your head

};