#pragma once
#include "Engine.h"
#include "Context.h"
#include "Utils/Patterns/NonCopyable.h"

class Engine;
class Camera;

class Application : public NonCopyable
{
public:
	Application( std::string applicationName );
	~Application();

	/* looping handle event */
	void CenteringMousePosition();
	void RunLoop();

	bool LockMouseInsideWindow();
	void CursorFocusWindow(bool);

private:
	void HandleEvents(sf::Event&);
	void cleanBuffer();
private:
	Context _context;
	Config _config;
	Engine* _pEngine{nullptr};
	sf::Clock _clock;

	bool cursorDisplay ;
	bool windowFocus;
	
};

/*
	application foscus con window and GUI level
*/

