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

	/* state update handle */
	void Update();
	void HandleEvent();

	/* make project view model matrix */
	void SetupCamMatrix();
	glm::mat4 GetViewMatrix() const ;
	glm::mat4 GetProjectionViewMatrix() const ;
	glm::mat4 GetProjectionMatrix() const ;

	void CalViewMatrix();
	void CalProjectionMatrix();

	void MoveUp(float );
	void MoveDown(float );
	void MoveLeft(float );
	void MoveRight(float );
	void MoveFront(float );
	void MoveBack(float );
	void MouseUpdate(const float&, const float&);

private:
	POVDATA m_sProjectionData;
	sf::Window* m_pWindow;

	/* saving matrix */
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionViewMatrix;

public:
	glm::vec3 m_viewDirection;
	glm::vec3 m_upPositipon;
	glm::vec3 m_position;

	float m_rSpeed{ 0.3f };		// yaw pitch roll sensitivity
	float m_mSpeed{ 0.05f };	// moving sensitivity
	float m_speed{ 5 };

	float m_yaw{ 0.0f };		// turn your head left and right
	float m_pitch{ 0.0f };		// turn your head up and down 
	//float m_roll;				// not using , rotate your head

};