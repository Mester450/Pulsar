#pragma once

#include "SFML/Graphics.hpp"
#include "Ngin.h"
#include "Starship.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h> 

class Enemy : public sf::Drawable {
public:
	Enemy(const sf::Vector2f& position) {
		_explosionSound.setBuffer(NG_SOUNDBUFFER("explosion.wav"));
		ngin::Audio::subscribeSound(&_explosionSound);

		_explosion.setTexture(NG_TEXTURE("explosion.png"));
		_explosion.setScale({ 0.5F, 0.5F});

		_shapeEnemy.setSize({ 200, 200 });
		_shapeEnemy.setScale({ 0.3f, 0.3f });

		_isAlive = true;
		_isTouching = false;
		_touched = false;
		_isOnScreen = true;

		_explosionTrigger = false;
		_explosionTimer = 0.0F;

		_shapeEnemy.setPosition(position);
		_explosion.setPosition(_shapeEnemy.getPosition());

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

	void setTexture(const sf::Texture& texture);

private:
	sf::RectangleShape _shapeEnemy;
	sf::Sprite _explosion;

	sf::Vector2f _movement; // the amount of movement in vector (random direction)
	static sf::Vector2f _speed; // the speed of movement

	static sf::Sound _explosionSound;

	bool _isAlive;
	bool _isTouching;
	bool _touched;
	bool _isOnScreen;

	bool _explosionTrigger;
	float _explosionTimer;
	const float _explosionLimit = 0.5F;
};