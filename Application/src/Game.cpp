#include "Game.h"

float Game::_scoreTime = 0.0F;
std::string Game::_scoreString;

void Game::setup()
{
	sf::FloatRect screen = { 0, 0 , 1366, 768 };
	Enemy::setSpeed({ 1.0F, 1.0F });
	_levelTimer = 0.0F;
	_waveNum = 1;
	_waveTimer = 0.0F;
	_drawWave = true;

	_scoreTextTime.setFont(*ngin::Resources::AcquireFont("arial.ttf"));
	_scoreTextTime.setCharacterSize(30);
	_scoreTextTime.setFillColor(sf::Color::White);

	_waveText.setFont(*ngin::Resources::AcquireFont("oldgame.ttf"));
	_waveText.setCharacterSize(90);
	_waveText.setString("Wave " + std::to_string(_waveNum));
	_waveText.setFillColor({ 214, 112, 28 });
	ngin::centerTextInBounds(_waveText, screen, -20);
}

void Game::handleEvents(const sf::Event& event)
{
	_starShip.handleEvents(event);
}

void Game::update()
{
	response_ = RESPONSES::RESPONSES_NONE;

	_starShip.update();

	if (!_drawWave)
	{
		for (int i = 0; i < _enemies.size(); i++) {
			_enemies[i].update(_starShip);
		}

		_spawnDeltaTime += ngin::Timer::getDeltaTime();
		if (_spawnDeltaTime >= _spawnTime) {
			_spawnDeltaTime = 0;

			generateEnemy();
		}

		_levelTimer += ngin::Timer::getDeltaTime();
		if (_levelTimer >= _timeLimit) {
			_levelTimer = 0.0F;

			_enemies.clear();
			Enemy::setSpeed({ Enemy::getSpeed().x + 0.5F, Enemy::getSpeed().y + 0.5F });

			_drawWave = true;
			_waveNum++;
			_waveText.setString("Wave " + std::to_string(_waveNum));
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
	else {
		_waveTimer += ngin::Timer::getDeltaTime();
		if (_waveTimer > _waveLimit) {
			_waveTimer = 0.0F;
			_drawWave = false;
		}
	}


}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_drawWave) {
		target.draw(_waveText);
	}
	else {
		for (int i = 0; i < _enemies.size(); i++) {
			_enemies[i].draw(target, states);
		}
	}

	_starShip.draw(target, states);
	target.draw(_scoreTextTime);
}

void Game::generateEnemy()
{
	_enemies.push_back(sf::Vector2f{ -500, -500 });
	sf::Vector2f enemyPos;

	sf::FloatRect safeZone = {
		_starShip.getGlobalBounds().left - 100 ,
		_starShip.getGlobalBounds().top - 100 ,
		_starShip.getGlobalBounds().width + 100 ,
		_starShip.getGlobalBounds().height + 100
	};

	do {
		enemyPos.x = rand() % static_cast<int>(1366 - _enemies[_enemies.size() - 1].getGlobalBounds().width);
		enemyPos.y = rand() % static_cast<int>(768 - _enemies[_enemies.size() - 1].getGlobalBounds().height);
		_enemies[_enemies.size() - 1].setPosition({ enemyPos.x, enemyPos.y });
	} while (_enemies.back().getGlobalBounds().intersects(safeZone));

}
