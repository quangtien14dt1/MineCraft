#include "Camera.h"


Camera::Camera() 
	: _pWindow(nullptr)
	, _position( glm::vec3(1.0f))
	, _sProjectionData()
	, _pEngine(nullptr)
{ /* do nothing */ }

Camera::Camera(const Context* c,Engine* e, float a, float closeP, float farP) {

	/* setup parameters */
	_sProjectionData.angle = a;
	_sProjectionData.width = c->_width;
	_sProjectionData.height = c->_height;
	_sProjectionData.closePlane = closeP;
	_sProjectionData.farPlane = farP;
	_pWindow = c->_pWindow;

	/* Engine */
	_pEngine = e;

	/*  */
	CamMatrix();
}

glm::mat4 Camera::CamMatrix() {

	glm::mat4 _viewMatrix = glm::lookAt(_position, _position + _viewDirection, _upPositipon);

	glm::mat4 _projectionMatrix = glm::perspective(
		glm::radians(_sProjectionData.angle),
		(float)_sProjectionData.width / (float)_sProjectionData.height,
		_sProjectionData.closePlane,
		_sProjectionData.farPlane);

	_camMatrix = _viewMatrix * _projectionMatrix;

	return _camMatrix;

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

void Camera::MoveUp(float e) { _position += e * _mSpeed * _upPositipon; };
void Camera::MoveDown(float e) { _position -= e * _mSpeed * _upPositipon; };
void Camera::MoveLeft(float e) { _position -= e * _mSpeed * glm::normalize(glm::cross(_viewDirection, _upPositipon)); };
void Camera::MoveRight(float e) { _position += e * _mSpeed * glm::normalize(glm::cross(_viewDirection, _upPositipon)); };
void Camera::MoveFront(float e) { _position += e * _mSpeed * _viewDirection; };
void Camera::MoveBack(float e) { _position -= e * _mSpeed * _viewDirection; };

