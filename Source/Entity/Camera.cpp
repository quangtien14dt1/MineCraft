#include "Camera.h"
#include "../glm.h"
#include "../Shader/BasicShader.h"
#include "../EventManager.h"
#include <iostream>


Camera::~Camera() { }

Camera::Camera(Config* cf, Context* ct)
	: _sensitivity(50.0f)
{

	/* setup parameters */
	_pContext = ct;
	_pConfig = cf;
	_sProjectionData.angle = cf->_angle;
	_sProjectionData.width = (float)cf->_width;
	_sProjectionData.height = (float)cf->_height;
	_sProjectionData.closePlane = cf->_close;
	_sProjectionData.farPlane = cf->_far;

	InitProjectionMatrix();
}

void Camera::CalculateViewMatrix() {
	_viewMatrix = glm::lookAt(_position, _position + _viewDirection, _upPosition);
}

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
}

void Camera::Update(sf::Event& e, float delta) {
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::A) { MoveLeft(delta); break; }
		if (e.key.code == sf::Keyboard::S) { MoveBackWard(delta);  break; }
		if (e.key.code == sf::Keyboard::D) { MoveRight(delta); break; }
		if (e.key.code == sf::Keyboard::W) { MoveForWard(delta); break; }
		if (e.key.code == sf::Keyboard::R) { RotateLeft(delta); break; };
		if (e.key.code == sf::Keyboard::T) { RotateRight(delta); break; };
		break;

	case sf::Event::MouseButtonPressed:
		if (e.mouseButton.button == 0) _dragging = true;
		_previousMousePosition = sf::Vector2i(
			sf::Mouse::getPosition(*(_pContext->_pWindow))
		);
		break;

	case sf::Event::MouseButtonReleased:
		_dragging = false;
		break;

	case sf::Event::MouseWheelScrolled:
		ProcessMouseScrolling(e);
		break;

	case sf::Event::MouseMoved:
		if (!_dragging) break;
		HandleMouseMoving(e, delta);
		break;

	default:
		break;
	}
}

void Camera::RotateLeft(float del) {
	float scale = _sensitivity * del;
	_yaw -= _sensitivity * scale;

}

void Camera::RotateRight(float del) {
	float scale = _sensitivity * del;
	_yaw += _sensitivity * del;

}


void Camera::ProcessMouseScrolling(sf::Event& e) {
	auto delta = e.mouseWheel.delta;
	if (delta) {
		_sProjectionData.angle += delta * 2;
		InitProjectionMatrix();
	}
	ToString();
}

void Camera::HandleMouseMoving(sf::Event& e, float delta) {
	auto currentMousePosition = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);
	const sf::Vector2i del = currentMousePosition - _previousMousePosition;

	// Move the camera based on the mouse movement
	float scale = _sensitivity * delta ;

	_yaw -= (float)del.x * scale;
	_pitch -= (float)del.y * scale;

	_position -= _right * (float)del.x * scale;
	_position -= _upPosition * (float)del.y * scale;

	_previousMousePosition = currentMousePosition;
	ToString();
}

void Camera::UpdateCameraVector() {
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_viewDirection = glm::normalize(front);
	_right = glm::normalize(glm::cross(_viewDirection, _upPosition));
	_upPosition = glm::normalize(glm::cross(_right, _viewDirection));

	CalculateViewMatrix();
}

/* moving */
void Camera::MoveBackWard(float delta) { 
		_position -= _viewDirection * _sensitivity * delta * 50; 
}

void Camera::MoveForWard(float delta) { 
	_position += _viewDirection * _sensitivity * delta * 50 ; 
}

void Camera::MoveLeft(float delta) { 
	_position -= _right * _sensitivity * delta * 50 ; 
}

void Camera::MoveRight(float delta) { 
	_position += _right * _sensitivity * delta * 50; 
}

void Camera::ToString() {
	std::cout << "View    : " << glm::to_string(_viewDirection) << std::endl;
	std::cout << "Right   : " << glm::to_string(_right) << std::endl;
	std::cout << "Up      : " << glm::to_string(_upPosition) << std::endl;
	std::cout << "Position: " << glm::to_string(_position) << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
}

void Camera::ZoomInOut(sf::Event&) {}