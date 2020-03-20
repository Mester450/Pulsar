#include "Enemy.h"

sf::Vector2f Enemy::_speed = { 0, 0 }; // default not moving
sf::Sound Enemy::_explosionSound; // sound it makes when it dies

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

				_explosionSound.play();

				_explosionTrigger = true;
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

		_shapeEnemy.move({
			_movement.x * ngin::Timer::getDeltaTime(),
			_movement.y * ngin::Timer::getDeltaTime(),
			});

		_explosion.setPosition(_shapeEnemy.getPosition());
	}
	
	if (_explosionTrigger) {
		_explosionTimer += ngin::Timer::getDeltaTime();
		if (_explosionTimer > _explosionLimit) {
			_explosionTimer = 0.0F;
			_explosionTrigger = false;
		}
	}
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_isOnScreen)
	{
		target.draw(_shapeEnemy);
	}

	if (_explosionTrigger)
	{
		target.draw(_explosion);
	}
}

void Enemy::setTexture(const sf::Texture& texture)
{
	_shapeEnemy.setTexture(&texture);
}
