#pragma once


#include "Context.h"
#include "Application.h"

#include <SFML/Window.hpp>
#include <vector>

/*
	Explain
	view * model * projection ( matrix 4 ) 
	Please what series videos of 3Blue1brown about euler formular 
	to understand about vector , matrix and coordinate system 
	basiclly we got a ball* with it own (xyz) , now we got a box with larger space
	and also it own (xyz) 
	1 - we need to push this model into that box ( model matrix ) that is position of model to world
	2 - we got eye also is point into that space ( view matrix ) how we see everything in that world
	2 - we got projection , (projection matrix ) an glass on our eye to transform how everthing appear
	in eye( monitor )
	because our monitor is 2D system 

	* we got Camera to handle view and projection 
	* model matrix will be the location how to put balls* into the box
*/

class Application;

class Camera;

class Mesh;

class BasicShader;

class Engine
{
public:
	Engine(Context*, Application*);

	~Engine();

	int  InitGame();

	void UpdateGameLogic(sf::Event&,float);

	void HandleKeyboard(sf::Event&, float );

	void HandleMouseMoving(sf::Event&, float);

	void HandleScrolling(sf::Event&);

	void Draw();
	
	int  RemoveData();

	void AddNewData(Mesh);

	void ErrorMessage(const char*);

private:

	Context*		_pContext;

	Application*	_pApplication; 

	Camera*			_camera;	

	BasicShader*	_shader;

	std::vector<Mesh> _vMesh;
};

