#include "Camera.h"


Camera::Camera(const Context* c, float a, float closeP, float farP) {
	/* initilizer matrix  */
	m_projectionMatrix = glm::mat4(1.0f);
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionViewMatrix = glm::mat4(1.0f);

	/* setup parameters */
	m_sProjectionData.angle = a;
	m_sProjectionData.width = c->m_width;
	m_sProjectionData.height = c->m_height;
	m_sProjectionData.closePlane = closeP;
	m_sProjectionData.farPlane = farP;
	m_pWindow = c->m_pWindow;

	/*  */
	SetupCamMatrix();
}

void Camera::SetupCamMatrix() {
	CalViewMatrix();
	CalProjectionMatrix();

	// projection view 
	m_projectionViewMatrix = m_viewMatrix * m_projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() const { return m_viewMatrix; }
glm::mat4 Camera::GetProjectionMatrix() const { return m_projectionMatrix; }
glm::mat4 Camera::GetProjectionViewMatrix() const { return m_projectionViewMatrix; } // for later change camera matrix

void Camera::CalViewMatrix() {
	m_viewMatrix = glm::lookAt(m_position, m_position + m_viewDirection, m_upPositipon);
};
void Camera::CalProjectionMatrix() {
	m_projectionMatrix = glm::perspective(
		glm::radians(m_sProjectionData.angle),
		(float)m_sProjectionData.width / (float)m_sProjectionData.height,
		m_sProjectionData.closePlane,
		m_sProjectionData.farPlane);
};

void Camera::Update() {};
void Camera::HandleEvent() {};

// basiclyy moving base on delta time collect from looping
// 
void Camera::MoveUp(float e) { m_position += e * m_mSpeed * m_upPositipon; };
void Camera::MoveDown(float e) { m_position -= e * m_mSpeed * m_upPositipon; };
void Camera::MoveLeft(float e) { m_position -= e * m_mSpeed * glm::normalize(glm::cross(m_viewDirection, m_upPositipon)); };
void Camera::MoveRight(float e) { m_position += e * m_mSpeed * glm::normalize(glm::cross(m_viewDirection, m_upPositipon)); };
void Camera::MoveFront(float e) { m_position += e * m_mSpeed * m_viewDirection; };
void Camera::MoveBack(float e) { m_position -= e * m_mSpeed * m_viewDirection; };

void Camera::MouseUpdate(const float& dx,const float& dy ) {
	m_yaw += dx * m_rSpeed;
	m_pitch += dy * m_rSpeed;

	if (m_pitch > 89.0f) m_pitch = 89.0f;
	if (m_pitch > 89.0f) m_pitch = 89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_viewDirection = glm::normalize(front);
};
