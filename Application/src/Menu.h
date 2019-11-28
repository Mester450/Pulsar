#pragma once
#include "SFML/Graphics.hpp"
#include "Ngin.h"

class Menu : public ngin::Level {
public:
	// gets called once in the beginning
	void setup();
	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update();
	// gets called every frame but should only draw on window
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	
	enum BUTTONS {
		STARTGAME = 0,
		HIGHSCORES,
		SETTINGS,
		EXIT
	};

	ngin::Button buttons[4]{
		{"Start Game", {400, 50}},
		{"HighScores", {400, 50}},
		{"Settings", {400, 50}},
		{"Exit Game", {400, 50}}
	};

	bool _canStartMove = true;
};