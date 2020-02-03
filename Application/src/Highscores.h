#pragma once
#include "Ngin.h"

class Highscores : public ngin::Level {
public:
	// gets called once in the beginning
	virtual void setup();
	// gets called only if there is an ongoing event
	virtual void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	virtual void update();
	// gets called every frame but should only draw on window
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSES {
		RESPONSES_NONE = 10,
		RESPONSES_BACK
	};

private:
	ngin::Button _back{ "Back", { 400, 50 } };
	sf::Text _highScores;

	std::vector<sf::Text> _scores;
	int _numOfScores = 10;

	bool _canStartMove = false;
};