#pragma once
#define MAIN_LEVEL

#include "NGin.h"

#include "Menu.h"
#include "Game.h"
#include "Settings.h"

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

	sf::View _view{ sf::FloatRect(0.0f, 0.0f, 1366.0f, 768.0f) };

	ngin::Level* _currentLevel;
};

ngin::MainLevel* setMainLevel() {
	return new Application;
}