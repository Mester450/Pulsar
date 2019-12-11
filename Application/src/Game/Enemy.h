#pragma once

#include "SFML/Graphics.hpp"
#include "Ngin.h"

class Enemy : public sf::Drawable {
public:
	Enemy() {
		_shapeEnemy.setTexture(&*ngin::Resources::AcquireTexture("Enemy.png"));
		_shapeEnemy.setSize({ 512, 512 });
		_shapeEnemy.setScale({ 0.2f, 0.2f });
		_shapeEnemy.setFillColor(sf::Color::Blue);

		_isAlive = true;
		_shapeEnemy.setPosition({ 1366 / 2 - _shapeEnemy.getGlobalBounds().width / 2, 768 / 2 - _shapeEnemy.getGlobalBounds().height / 2 });
	}

	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update();
	// gets called every frame but should only draw on window
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape _shapeEnemy;
	

	bool _isAlive;
};