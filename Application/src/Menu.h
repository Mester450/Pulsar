#pragma once
#include "SFML/Graphics.hpp"
#include "Ngin.h"

class Menu : public ngin::Level {
public:
	// gets called once in the beginning-
	void setup();
	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update();
	// gets called every frame but should only draw on window
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSES {
		RESPONSES_NONE = 0,
		RESPONSES_START,
		RESPONSES_HIGHSCORES,
		RESPONSES_SETTINGS,
		RESPONSES_EXIT
	};

private:
	
	enum BUTTONS {
		BUTTONS_START = 0,
		BUTTONS_HIGHSCORES,
		BUTTONS_SETTINGS,
		BUTTONS_EXIT,
		BUTTONS_SIZE
	};

	ngin::Button buttons[BUTTONS_SIZE]{
		{"Start Game", {400, 50}},
		{"HighScores", {400, 50}},
		{"Settings", {400, 50}},
		{"Exit Game", {400, 50}}
	};

	bool _canStartMoves[BUTTONS_SIZE];
};