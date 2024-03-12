#include "Camera.h"
#include "../glm.h"
#include "../Shader/BasicShader.h"

#include <iostream>


Camera::Camera() 
	: _pWindow(nullptr)
	, _sProjectionData()

{ /* do nothing */ }

Camera::Camera(const Context* c, float a, float closeP, float farP) {

	/* setup parameters */
	_sProjectionData.angle = a;

	_sProjectionData.width = c->_width;

	_sProjectionData.height = c->_height;

	_sProjectionData.closePlane = closeP;

	_sProjectionData.farPlane = farP;

	_pWindow = c->_pWindow;

	ProjectionMatrix();

	ViewMatrix();

	UpdateCameraVector();

}

glm::mat4 Camera::ViewMatrix() { 

	_viewMatrix = glm::lookAt(_position, _position + _viewDirection, _upPosition);

	return _viewMatrix;

}

void Camera::ProcessKeyboard( Camera_Movement direction, float delta ) {

	std::cout << "delta: " << delta << std::endl;

	float velocity = _speed * delta;

	switch (direction)
	{
	case FORWARD:
		_position += _viewDirection * velocity;
		break;
	case BACKWARD:
		_position -= _viewDirection * velocity;
		break;
	case LEFT:
		_position -= _right * velocity;
		break;
	case RIGHT:
		_position += _right * velocity;
		break;
	default:
		break;
	}

	ViewMatrix();

	UpdateCameraVector();
}

void Camera::UniformMatrix(BasicShader& s ) {

	s.LoadProjectionMatrix(_projectionMatrix);

	s.LoadViewMatrix(_viewMatrix);

};

glm::mat4 Camera::ProjectionMatrix() {

	_projectionMatrix = glm::perspective(
		glm::radians(_sProjectionData.angle),
		(float)_sProjectionData.width / (float)_sProjectionData.height,
		_sProjectionData.closePlane,
		_sProjectionData.farPlane);

	return _projectionMatrix;

}

void Camera::MouseUpdate(const float& dx,const float& dy ) {

	_yaw += dx * _rSpeed;

	_pitch += dy * _rSpeed;

	if (_pitch > 89.0f) _pitch = 89.0f;

	if (_pitch > 89.0f) _pitch = 89.0f;

	glm::vec3 front;

	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	front.y = sin(glm::radians(_pitch));

	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_viewDirection = glm::normalize(front);
};

void Camera::UpdateCameraVector() {

	glm::vec3 front;

	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	front.y = sin(glm::radians(_pitch));

	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_viewDirection = glm::normalize(front);

	// also re-calculate the Right and Up vector
	_right = glm::normalize(glm::cross(_viewDirection, _upPosition));

	_upPosition = glm::normalize(glm::cross(_right, _viewDirection));
}

void Camera::ProcessMouseScrolling(sf::Event& e) {

	if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
		if (e.mouseWheelScroll.delta > 0) {
			// scroll up
		}
		else if (e.mouseWheelScroll.delta < 0) {
			// scroll down 
		}
	}
};

