#pragma once
#include "Engine.h"
#include "Context.h"
#include "Singleton.h"

class Engine;
class Camera;

class Application : public SingleTon
{
public:
	Application();
	~Application();

	/* looping handle event */
	void CenteringMousePosition();
	void RunLoop();
	void TurnOffMouse();
	void TurnOnMouse();
	
private:
	void HandleEvents(sf::Event&);
private:
	Context _context;
	Config _config;
	Engine* _pEngine{nullptr};
	sf::Clock _clock;
};

/*
	application foscus con window and GUI level
*/

