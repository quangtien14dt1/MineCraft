#pragma once

#include <iostream>
#include <list>
#include <string>
#include <SFML/Window.hpp>


class IObserver {
public:
	virtual ~IObserver() {};
	virtual void Update( sf::Event& e,float d) = 0;
};

class ISubject {
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify(sf::Event&, float) = 0;
};