#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#include "SFML/Graphics.hpp"
#include "Ngin.h"

#include "Game/Starship.h"

#include "Game/Enemy.h"

class Game : public ngin::Level {
public:
	
	Game() {
		_enemy.push_back(sf::Vector2f{ -500, -500 });
		sf::Vector2f enemyPos;

		srand(time(NULL));
		enemyPos.x = rand() % static_cast<int>(1366 - _enemy[_enemy.size() - 1].getGlobalBounds().width);
		enemyPos.y = rand() % static_cast<int>(768 - _enemy[_enemy.size() - 1].getGlobalBounds().height);
		_enemy[_enemy.size() - 1].setPosition({ enemyPos.x, enemyPos.y });

	}
	// gets called once in the beginning-
	void setup();
	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update();
	// gets called every frame but should only draw on window
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	std::vector<Enemy> _enemy;

	float _spawnTime = 1.0f;
	float _spawnDeltaTime = 0.0f;
	
	Starship _starShip;
};
