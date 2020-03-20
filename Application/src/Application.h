#pragma once
#define MAIN_LEVEL

#include "NGin.h"

#include "Menu.h"
#include "Game.h"
#include "Settings.h"
#include "Endscreen.h"
#include "Highscores.h"
#include "Highscores/ReadWrite.h"

#include "Music/Music.h"

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
	sf::Sprite _background;

	ngin::Level* _currentLevel;

	ReadWrite _readWrite;

	const sf::Vector2f cursorScale_ = { 0.5F, 0.5F };
};

ngin::MainLevel* setMainLevel() {
	return new Application;
}