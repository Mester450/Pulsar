#pragma once

#include "SFML/Graphics.hpp"
#include "Ngin.h"

class Starship : public sf::Drawable {
public:
	Starship() {
		_shape.setTexture(&*ngin::Resources::AcquireTexture("Starship.png"));
		_shape.setSize({ 512, 512 });
		_shape.setScale({ 0.2f, 0.2f });
		_shape.setFillColor(sf::Color::Blue);

		_isAlive = true;
		_shape.setPosition({ 1366 / 2 - _shape.getGlobalBounds().width / 2, 768 / 2 - _shape.getGlobalBounds().height / 2 });
	}

	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update();
	// gets called every frame but should only draw on window
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape _shape;
	float _speed = 500.0F;

	bool _isAlive;
};