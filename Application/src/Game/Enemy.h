#pragma once

#include "SFML/Graphics.hpp"
#include "Ngin.h"
#include "Starship.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h> 

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


		sf::Vector2i randNum;

		if (rand() % 2 == 1) {
			randNum.x = 1;
		}
		else {
			randNum.x = -1;
		}

		if (rand() % 2 == 1) {
			randNum.y = 1;
		}
		else {
			randNum.y = -1;
		}

		_movement = { randNum.x * _speed.x,
			          randNum.y * _speed.y };

	}

	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update(Starship& starship);
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool getIsOnScreen() {
		return _isOnScreen;
	}

	sf::FloatRect getGlobalBounds() {
		return _shapeEnemy.getGlobalBounds();
	}

	void setPosition(const sf::Vector2f& position) {
		_shapeEnemy.setPosition(position);
	}

	static sf::Vector2f getSpeed() {
		return _speed;
	}

	static void setSpeed(sf::Vector2f in_speed) {
		_speed = in_speed;
	}


private:
	sf::RectangleShape _shapeEnemy;
	sf::Vector2f _movement;
	static sf::Vector2f _speed;

	bool _isAlive;
	bool _isTouching;
	bool _touched;
	bool _isOnScreen;

};