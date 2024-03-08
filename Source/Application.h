#pragma once


#include "Engine.h"


/*
* Application will focus on GUI 
*/

class Context;

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

	bool _running;

private:
	void HandleEvents(sf::Event&);

	Context* _pContext{nullptr};

	Engine* _pEngine{nullptr};
};

