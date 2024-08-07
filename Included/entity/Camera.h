#pragma once

#include "glm.h"
#include "context.h"
#include "engine.h"
#include "utils/patterns/observerpattern.h"
#include "utils/patterns/singleton.h"


/* POV parameter  */
struct POVDATA {
	float	angle;
	float	width;
	float	height;
	float	closePlane;
	float	farPlane;
};

class BasicShader;

class Camera : public IObserver, public SingleTon {

public:
	Camera(Config*, Context*);
	~Camera();
	/* make project view model matrix */;
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void CalculateViewMatrix();
	void InitProjectionMatrix();

	void Update(sf::Event& e, float ) override;

	/*  camera update state functions */
	void MoveBackWard(float);
	void MoveForWard(float);
	void MoveLeft(float);
	void MoveRight(float);

	/*  development phase for camera rolling 
		using for single direction 

	*/
	void TurnUp_Down(int);
	void RotateLeft(float);
	void RotateRight(float);

	void HandleMouseMoving(sf::Event&, float );

	/* mouse event */
	void ZoomInOut(sf::Event&);

	/*  update variables */
	void UpdateSensitivity(float);
	void UpdateSpeed(float);

	void ProcessMouseScrolling(sf::Event&);

	void ToString();
	/* recalculate and normalize base vectors */
	void UpdateCameraVector();
private:
	POVDATA _sProjectionData;

	Application* _pApplication{ nullptr };
	Context* _pContext{nullptr};
	Config* _pConfig{ nullptr };

	
public:
	glm::mat4 _viewMatrix = glm::mat4(1.0f);
	glm::mat4 _projectionMatrix = glm::mat4(1.0f);

	/* camera it own direction */
	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 _viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _upPosition = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 _right;

	/* yaw = 0 equal to direction vector pointing to the right */
	float _yaw{ -90.0f }; 
	float _pitch{ 0.0f };

	bool _dragging;
	sf::Vector2i _previousMousePosition;
	bool _constrainPitch = true;
	float _sensitivity = 5;
};