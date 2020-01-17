#include "Game.h"

void Game::setup()
{
}

void Game::handleEvents(const sf::Event& event)
{
	_starShip.handleEvents(event);
}

void Game::update()
{
	_starShip.update();

	for (int i = 0; i < _enemy.size(); i++) {
		_enemy[i].update(_starShip);
	}


	_spawnDeltaTime += ngin::Timer::getDeltaTime();
	if (_spawnDeltaTime >= _spawnTime) {
		_spawnDeltaTime = 0;

		_enemy.push_back(sf::Vector2f{ -500, -500 });
		sf::Vector2f enemyPos;

		srand(time(NULL));
		enemyPos.x = rand() % static_cast<int>(1366 - _enemy[_enemy.size() - 1].getGlobalBounds().width);
		enemyPos.y = rand() % static_cast<int>(768 - _enemy[_enemy.size() - 1].getGlobalBounds().height);
		_enemy[_enemy.size() - 1].setPosition({ enemyPos.x, enemyPos.y });

	}
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < _enemy.size(); i++) {
		_enemy[i].draw(target, states);
	}

	_starShip.draw(target, states);
}
