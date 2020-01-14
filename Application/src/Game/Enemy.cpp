#include "Enemy.h"

void Enemy::handleEvents(const sf::Event& event)
{

}

void Enemy::update(Starship& starship)
{
	if (starship.getGlobalBounds().intersects(_shapeEnemy.getGlobalBounds())) {
		_isTouching = true;

		if (_isTouching && _touched == false) {
			starship.setLives(starship.getLives() - 1);
		}

		_touched = true;
	}
	else {
		_touched = false;
	}

	if (_shapeEnemy.getPosition().x + _shapeEnemy.getGlobalBounds().width > ngin::MainLevel::getView().getSize().x ||
		_shapeEnemy.getPosition().y + _shapeEnemy.getGlobalBounds().height > ngin::MainLevel::getView().getSize().y ||
		_shapeEnemy.getPosition().x < 0 ||
		_shapeEnemy.getPosition().y < 0)
	{
		_isOnScreen = false;
	}

	_shapeEnemy.move( 1, 1);






}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shapeEnemy);
}
