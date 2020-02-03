#include "Game.h"

float Game::_scoreTime = 0.0F;
std::string Game::_scoreString;

void Game::setup()
{
	_scoreTextTime.setFont(*ngin::Resources::AcquireFont("arial.ttf"));
	_scoreTextTime.setCharacterSize(30);
	_scoreTextTime.setFillColor(sf::Color::White);
	

}

void Game::handleEvents(const sf::Event& event)
{
	_starShip.handleEvents(event);
}

void Game::update()
{
	response_ = RESPONSES::RESPONSES_NONE;

	_starShip.update();

	for (int i = 0; i < _enemy.size(); i++) {
		_enemy[i].update(_starShip);
	}


	_spawnDeltaTime += ngin::Timer::getDeltaTime();
	if (_spawnDeltaTime >= _spawnTime) {
		_spawnDeltaTime = 0;

		generateEnemy();

	}

	if (_starShip.isAlive()) {
		_scoreTime += ngin::Timer::getDeltaTime();
		_scoreString = std::to_string(_scoreTime);
		_scoreTextTime.setString(_scoreString);
	}
	else {
		response_ = RESPONSES::RESPONSES_ENDSCREEN;
	}

}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (int i = 0; i < _enemy.size(); i++) {
		_enemy[i].draw(target, states);
	}

	_starShip.draw(target, states);

	target.draw(_scoreTextTime);
}

void Game::generateEnemy()
{
	_enemy.push_back(sf::Vector2f{ -500, -500 });
	sf::Vector2f enemyPos;

	sf::FloatRect safeZone = {
		_starShip.getGlobalBounds().left - 50 ,
		_starShip.getGlobalBounds().top - 50 ,
		_starShip.getGlobalBounds().width + 50 ,
		_starShip.getGlobalBounds().height + 50
	};

	do {
		enemyPos.x = rand() % static_cast<int>(1366 - _enemy[_enemy.size() - 1].getGlobalBounds().width);
		enemyPos.y = rand() % static_cast<int>(768 - _enemy[_enemy.size() - 1].getGlobalBounds().height);
		_enemy[_enemy.size() - 1].setPosition({ enemyPos.x, enemyPos.y });
	} while (_enemy.back().getGlobalBounds().intersects(safeZone));

}
