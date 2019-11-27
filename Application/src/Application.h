#pragma once
#define MAIN_LEVEL

#include "NGin.h"

#include "Menu.h"

class Application : public ngin::MainLevel
{
public:
	Application();

	/* abstract overrides */
	virtual void setup();
	virtual void handleEvents();
	virtual void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

	ngin::Level* _currentLevel;
};

ngin::MainLevel* setMainLevel() {
	return new Application;
}