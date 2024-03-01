#pragma once


#include "Context.h"
#include "EventManager.h"
#include "KeyBoard.h"
#include "entity/Camera.h"
#include "shader/BasicShader.h"
#include "texture/Texture.h"
#include "ModelLoading.h"
#include "Mesh.h"
#include "Application.h"

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

class Engine
{
public:
	Engine(Context*, Application*);
	~Engine();

	int  InitGame();
	int  UpdateGameLogic(float);
	void HandleKeyboard(sf::Event&, float );
	void HandleMouseMoving(sf::Event&, float);
	void HandleScrolling(sf::Event&, float);
	void Draw();
	
	int  RemoveData();
	void AddNewData(Mesh&);
	void ErrorMessage(const char*);

private:

	Context*		m_pContext;
	Application*	m_pApplication; 

	Camera			m_camera;	
	Keyboard		m_keyboard;
	BasicShader		m_shader;

	//std::vector<Texture> m_vTexs;	// stored value 
	std::vector<Mesh> m_vMesh;
};
