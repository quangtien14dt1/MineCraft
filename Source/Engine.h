#pragma once

#include "Context.h"
#include "Application.h"
#include "Utils/Patterns/ObserverPatter.h"
#include "Utils/Patterns/SingleTon.h"
#include <SFML/Window.hpp>
#include <vector>
#include <memory>

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
class BasicShader;
class Model;
class Render;
class BlockDatabase;
class BlockFactory;

class Engine : public ISubject, public SingleTon
{
public:
	Engine(Config*, Application*, Context*);

	~Engine();
	static Engine* GetInstance(Config*, Application*, Context*);
	//int  InitGame();

	/* Logic Handle for Event level */
	void UpdateGameLogic(sf::Event&,float);

	void Invoke();
	int  RemoveData();
	void AddNewData(  const std::shared_ptr<Model> );
	void ErrorMessage(const char*);

	/* Handle ISubject Camera */
	void Attach(IObserver* observer) override;
	void Detach(IObserver* observer) override;
	void Notify(sf::Event&, float ) override;
	Camera* GetCamera();
	
	/* load data */
	void LoadMap();

	void LoadModeRender();
	void SetRenderMode( bool);
	bool GetRenderMode();

private:
	bool _polyMode;
	static Engine* _pEngine;
	BlockDatabase* _blockDatabase;
	BlockFactory* _blockFactory;
	Config*		_pConfig;
	Context*		_pContext;
	Application*	_pApplication; 
	Camera*			_camera;	
	Render*	_renderMaster;
	std::vector< std::shared_ptr< Model> > _vModel;
	std::list<IObserver*> _observer;
};

