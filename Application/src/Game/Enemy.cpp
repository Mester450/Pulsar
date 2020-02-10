#include "Enemy.h"

sf::Vector2f Enemy::_speed = {1, 1};

void Enemy::handleEvents(const sf::Event& event)
{

}

void Enemy::update(Starship& starShip)
{
	if (_isOnScreen) {
		// --- erintkezes az idegennel --------------------
		if (starShip.getGlobalBounds().intersects(_shapeEnemy.getGlobalBounds())) {
			_isTouching = true;

			if (_isTouching && _touched == false && starShip.isAlive()) {
				// --- levesz az eletbol es letorli az ellenseget amelyikkel erintkezik ---
				starShip.setLives(starShip.getLives() - 1);
				_isOnScreen = false;
			}

			_touched = true;
		}
		else {
			_touched = false;
		}
		// ------------------------------------------------

		// --- visszaverodes a szelekkel --------------------
		if (_shapeEnemy.getPosition().x + _shapeEnemy.getGlobalBounds().width > ngin::MainLevel::view_.getSize().x ||
			_shapeEnemy.getPosition().x < 0)
		{
			_movement.x = -_movement.x;
		}
		else if (_shapeEnemy.getPosition().y + _shapeEnemy.getGlobalBounds().height > ngin::MainLevel::view_.getSize().y ||
			_shapeEnemy.getPosition().y < 0)
		{
			_movement.y = -_movement.y;
		}
		// --------------------------------------------------

		_shapeEnemy.move(_movement);
	}
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_isOnScreen)
	{
		target.draw(_shapeEnemy);
	}
}
