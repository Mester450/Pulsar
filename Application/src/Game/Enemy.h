#pragma once

#include "SFML/Graphics.hpp"
#include "Ngin.h"
#include "Starship.h"

class Enemy : public sf::Drawable {
public:
	Enemy(const sf::Vector2f& position) {
		_shapeEnemy.setTexture(&*ngin::Resources::AcquireTexture("Enemy.png"));
		_shapeEnemy.setSize({ 200, 200 });
		_shapeEnemy.setScale({ 0.2f, 0.2f });
		_shapeEnemy.setFillColor(sf::Color::Red);

		_isAlive = true;
		_isTouching = false;
		_touched = false;
		_isOnScreen = true;
		//_shapeEnemy.setPosition({ 1366 / 2 - _shapeEnemy.getGlobalBounds().width / 2, 768 / 2 - _shapeEnemy.getGlobalBounds().height / 2 });
		_shapeEnemy.setPosition(position);

	}

	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update(Starship& starship);
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool getIsOnScreen() {
		return _isOnScreen;
	}


private:
	sf::RectangleShape _shapeEnemy;
	
	bool _isAlive;
	bool _isTouching;
	bool _touched;
	bool _isOnScreen;

};