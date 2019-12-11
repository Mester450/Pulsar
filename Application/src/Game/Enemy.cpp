#include "Enemy.h"

void Enemy::handleEvents(const sf::Event& event)
{

}

void Enemy::update()
{

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shapeEnemy);
}
