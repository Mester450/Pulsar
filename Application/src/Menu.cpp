#include "Menu.h"

void Menu::setup() {


	for (int i = 0; i < 4; i++) {
		buttons[i].setTexture(*ngin::Resources::AcquireTexture("button.png"));
		buttons[i].setFont(*ngin::Resources::AcquireFont("arial.ttf"));
		buttons[i].setPosition({ 200,300 + static_cast<float>(i) * 100 });
		buttons[i].setSelectThickness(0);
		buttons[i].setFillColor({ 28, 105, 214 });
		buttons[i].setTextColor({ 214, 112, 28 });
	}
}

void Menu::handleEvents(const sf::Event& event)
{

	for (int i = 0; i < 4; i++) {

		buttons[i].handleEvents(event, ngin::Cursor::getPosition());

		if (buttons[i].isSelected()) {

			buttons[i].setScale({ 1.01f,1.01f });

			if (_canStartMove) {
				const float x = buttons[i].getPosition().x - (buttons[i].getSize().x * buttons[i].getScale().x - buttons[i].getSize().x) / 2;
				const float y = buttons[i].getPosition().y - (buttons[i].getSize().y * buttons[i].getScale().y - buttons[i].getSize().y) / 2;
				buttons[i].setPosition({ x,y });

				_canStartMove = false;
			}

		}
		else {

			if (!_canStartMove) {
				const float x = buttons[i].getPosition().x + (buttons[i].getSize().x * buttons[i].getScale().x - buttons[i].getSize().x) / 2;
				const float y = buttons[i].getPosition().y + (buttons[i].getSize().y * buttons[i].getScale().y - buttons[i].getSize().y) / 2;
				buttons[i].setPosition({ x,y });

				_canStartMove = true;
			}

			buttons[i].setScale({ 1,1 });

		}
	}
}

void Menu::update() {
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < 4; i++) {
		target.draw(buttons[i]);
	}
}