#pragma once

#include "Ngin.h"
#include "Game.h"


class Endscreen : public ngin::Level {
public:
	Endscreen() {
	}
	// gets called once in the beginning-
	void setup();
	
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update();
	// gets called every frame but should only draw on window
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSES {
		RESPONSES_NONE = 8,
		RESPONSES_BACK
	};

	static std::string getPlayerName()
	{
		return _nameString;
	}

private:

	ngin::InputText _playerName;

	sf::Text _gameOver;
	sf::Text _score;
	ngin::Button button{
	"Back", {400, 50}
	};

	bool _canStartMove = false;
	static std::string _nameString;
		
	

};