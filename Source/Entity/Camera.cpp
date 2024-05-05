#include "Camera.h"
#include "../glm.h"
#include "../Shader/BasicShader.h"
#include "../EventManager.h"
#include <iostream>


Camera::~Camera() { }

Camera::Camera(Config* cf, Context* ct) {

	/* setup parameters */
	_pContext = ct;
	_pConfig = cf;
	_sProjectionData.angle = cf->_angle;
	_sProjectionData.width = cf->_width;
	_sProjectionData.height = cf->_height;
	_sProjectionData.closePlane = cf->_close;
	_sProjectionData.farPlane = cf->_far;

	InitProjectionMatrix();
	//UpdateCameraVector(); // calculate right vector
}

void Camera::CalculateViewMatrix() { 
	_viewMatrix = glm::lookAt(_position, _position + _viewDirection, _upPosition);  
};

glm::mat4 Camera::GetViewMatrix() {
	_viewMatrix = glm::lookAt(_position, _position + _viewDirection, _upPosition);
	return _viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() { return _projectionMatrix; }

void Camera::InitProjectionMatrix() {
	_projectionMatrix = glm::perspective(
		glm::radians(_sProjectionData.angle),
		_sProjectionData.width / _sProjectionData.height,
		_sProjectionData.closePlane,
		_sProjectionData.farPlane);

};

void Camera::UpdateDragging(bool d) {
	/* should not be dragging option*/
	_dragging = d;
}

void Camera::Update(sf::Event& e, float delta) {

	// thinking about checking poll event 
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::A) { MoveLeft(); break; };
		if (e.key.code == sf::Keyboard::S) { MoveBackWard();  break; };
		if (e.key.code == sf::Keyboard::D) { MoveRight(); break; };
		if (e.key.code == sf::Keyboard::W) { MoveForWard(); break;};

		/* this for development phase camera rotating */
		if (e.key.code == sf::Keyboard::L) { TurnLeft_Right(1); break; };
		if (e.key.code == sf::Keyboard::H) { TurnLeft_Right(-1); break; };
		if (e.key.code == sf::Keyboard::K) { TurnUp_Down(1); break; };
		if (e.key.code == sf::Keyboard::J) { TurnUp_Down(-1); break; };

	case (sf::Event::MouseButtonPressed):
		UpdateDragging(true);
		break;
	case (sf::Event::MouseButtonReleased):
		UpdateDragging(false);
		break;
		/*case (sf::Event::MouseMoved):
			ProcessMoveMoving(e);
			break;*/
	case sf::Event::MouseWheelScrolled:
		// ProcessMouseScrolling(e);
		break;
	default:
		break;
	}

	
};

void Camera::UpdateCameraVector() {

	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	
	/* normalize camera vector */
	_viewDirection = glm::normalize(front);
	_right = glm::normalize(glm::cross(_viewDirection, _upPosition));
	_upPosition = glm::normalize(glm::cross(_right, _viewDirection));

	CalculateViewMatrix();
}

/* moving  */
void Camera::MoveBackWard() { _position -= _viewDirection * _speed; ToString();};
void Camera::MoveForWard() { _position += _viewDirection * _speed; ToString(); };
void Camera::MoveLeft() { _position -= _right * _speed; ToString();};
void Camera::MoveRight() { _position += _right * _speed; ToString(); };

/* rotating */
void Camera::TurnUp_Down(int d) {

	_pitch += d * _rSpeed;
	
	if (_pitch > 89.0f) { _pitch = 89.0f; }
	if (_pitch < -89.0f) { _pitch = -89.0f; }

	ToString();
};

void Camera::TurnLeft_Right(int d) {
	/* handle for yaw */
	_yaw += d * _rSpeed;
	ToString();
};


void Camera::ToString() {
	std::cout << "View    : " << glm::to_string(_viewDirection) << std::endl;
	std::cout << "Right   : " << glm::to_string(_right) << std::endl;
	std::cout << "Up      : " << glm::to_string(_upPosition) << std::endl;
	std::cout << "Position: " << glm::to_string(_position) << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
};

void Camera::ZoomInOut(sf::Event&) {};