#include "Camera.h"
#include "../glm.h"
#include "../Shader/BasicShader.h"
#include "../EventManager.h"

#include <iostream>


Camera::~Camera() { }
	//if (_pContext != NULL) delete _pContext; _pContext = nullptr;
	//if (_pConfig != NULL) delete _pConfig; _pConfig = nullptr;


Camera::Camera(Config* cf, Context* ct) {

	/* setup parameters */
	_pContext = ct;
	_pConfig = cf;
	_sProjectionData.angle = cf->_angle;
	_sProjectionData.width = cf->_width;
	_sProjectionData.height = cf->_height;
	_sProjectionData.closePlane = cf->_close;
	_sProjectionData.farPlane = cf->_far;

	ProjectionMatrix();
	ViewMatrix();
	UpdateCameraVector();
}

glm::mat4 Camera::ViewMatrix() { 
	_viewMatrix = glm::lookAt(_position, _position + _viewDirection, _upPosition);
	return _viewMatrix;
}

void Camera::UniformMatrix(BasicShader& s ) {
	s.LoadProjectionMatrix(_projectionMatrix);
	s.LoadViewMatrix(_viewMatrix);
};

glm::mat4 Camera::ProjectionMatrix() {

	_projectionMatrix = glm::perspective(
		glm::radians(_sProjectionData.angle),
		_sProjectionData.width / _sProjectionData.height,
		_sProjectionData.closePlane,
		_sProjectionData.farPlane);

	return _projectionMatrix;

}

void Camera::UpdateDragging(bool d) {
	/* should not be dragging option*/
	_dragging = d;
}

void Camera::ProcessMoveMoving(sf::Event& e ) {

	if (_dragging) {
		float dx = float(e.mouseMove.x - _pContext->_pWindow->getSize().x);
		float dy = float(e.mouseMove.y - _pContext->_pWindow->getSize().y);

		_yaw += dx * _rSpeed;
		_pitch += dy * _rSpeed;

		if (_pitch > 89.0f) _pitch = 89.0f;
		if (_pitch > 89.0f) _pitch = 89.0f;

		/* normalize view vector direction */
		glm::vec3 front;
		front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		front.y = sin(glm::radians(_pitch));
		front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_viewDirection = glm::normalize(front);
	}

	ViewMatrix();
	UpdateCameraVector();
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
}

void Camera::ProcessKeyboard(sf::Event& e, float d) {
	float velocity = _speed * d;
	switch (e.key.code)
	{
	case sf::Keyboard::W:
		_position += _viewDirection * velocity;
		break;
	case sf::Keyboard::S:
		_position -= _viewDirection * velocity;
		break;
	case sf::Keyboard::A:
		_position -= _right * velocity;
		break;
	case sf::Keyboard::D:
		_position += _right * velocity;
		break;
	default:
		break;
	}
	ViewMatrix();
	UpdateCameraVector();
}

void Camera::Update(sf::Event& e, float delta ) {
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		ProcessKeyboard(e, delta);
		break;

	case (sf::Event::MouseButtonPressed):
		UpdateDragging(true);
		break;
	case (sf::Event::MouseButtonReleased):
		UpdateDragging(false);
		break;
	case (sf::Event::MouseMoved):
		ProcessMoveMoving(e);
		break;
	case sf::Event::MouseWheelScrolled:
		// ProcessMouseScrolling(e);
		break;
	default:
		break;
	}

};
