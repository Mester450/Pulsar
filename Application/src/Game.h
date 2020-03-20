#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#include "SFML/Graphics.hpp"
#include "Ngin.h"

#include "Game/Starship.h"

#include "Game/Enemy.h"
#include "Music/Music.h"

class Game : public ngin::Level {
public:
	enum RESPONSES {
		RESPONSES_NONE = 5,
		RESPONSES_ENDSCREEN,
		RESPONSES_EXIT
	};
	
	Game() {
		_scoreTime = 0.0F; // reset score
	}
	// gets called once in the beginning-
	void setup();
	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update();
	// gets called every frame but should only draw on window
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	static std::string getScoreString() {
		return _scoreString;
	}

	static float getScoreFloat() {
		return _scoreTime;
	}

private:
	unsigned enemyType = 0;
	void generateEnemy();

	std::vector<Enemy> _enemies;

	float _spawnTime = 1.0F;
	float _spawnDeltaTime = 0.0F;

	float _levelTimer = 0.0F;
	const float _timeLimit = 20.0F;
	
	static float _scoreTime;
	static std::string _scoreString;

	Starship _starShip;
	sf::Text _scoreTextTime;

	sf::Text _waveText;
	float _waveTimer = 0.0F;
	const float _waveLimit = 3.0F;
	int _waveNum = 1;
	bool _drawWave;
};
