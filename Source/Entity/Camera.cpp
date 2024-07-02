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
	_sProjectionData.width = (float)cf->_width;
	_sProjectionData.height = (float)cf->_height;
	_sProjectionData.closePlane = cf->_close;
	_sProjectionData.farPlane = cf->_far;

	InitProjectionMatrix();
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

		if(e.mouseButton.button == 0 ) _dragging = true;

		_previousMousePosition = sf::Vector2i(
			sf::Mouse::getPosition(*(_pContext->_pWindow))
		);
		break;

	case (sf::Event::MouseButtonReleased):
		_dragging = false;
		break;

	case sf::Event::MouseWheelScrolled:
		ProcessMouseScrolling(e);
		break;

	case sf::Event::MouseMoved:
		if (!_dragging) break;
		HandleMouseMoving(e);
		break;

	default:
		break;
	}

	
};

void Camera::ProcessMouseScrolling(sf::Event& e) {
	// so basiclly zoom in out equal to change the FOV camera
	// =>  changing angle FOV
	auto delta = e.mouseWheel.delta;
	if (delta) {
		_sProjectionData.angle += delta * 2;
		InitProjectionMatrix();
	}

	ToString();
};

void Camera::HandleMouseMoving(sf::Event& e) {

	auto currentMousePosition = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);
	const sf::Vector2i del = _previousMousePosition - currentMousePosition;

	/* like the real FPS gam e, should only handle X axis */
	_pitch -= del.y * _rSpeed ;

	if (_constrainPitch) {
		if (_pitch > 89.0f) { _pitch = 89.0f; }
		if (_pitch < -89.0f) { _pitch = -89.0f; }
	}
	
	_yaw += del.x * _rSpeed;

	_previousMousePosition = currentMousePosition;
	ToString();
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