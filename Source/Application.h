#pragma once

#include "Context.h"
#include "Engine.h"


/*
* Application will focus on GUI 
*/

class Engine;

class Application
{
public:
	Application();
	~Application();
	void RunLoop();
	void TurnOffMouse();
	void TurnOnMouse();
	void CenteringMousePosition();

private:
	void HandleEvents();

	Context* m_pContext{nullptr};
	Engine* m_pEngine{nullptr};
};

