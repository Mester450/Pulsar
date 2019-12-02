#include "Menu.h"

void Menu::setup() {


	for (int i = 0; i < 4; i++) {
		buttons[i].setTexture(*ngin::Resources::AcquireTexture("button.png"));
		buttons[i].setFont(*ngin::Resources::AcquireFont("arial.ttf"));
		buttons[i].setPosition({ 1000 / 2-buttons[i].getSize().x / 2, 300 + static_cast<float>(i) * 100 });
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

			buttons[i].setScale({ 1.02f,1.02f });

			if (_canStartMoves[i]) {
				const float x = buttons[i].getPosition().x - (buttons[i].getSize().x * buttons[i].getScale().x - buttons[i].getSize().x) / 2;
				const float y = buttons[i].getPosition().y - (buttons[i].getSize().y * buttons[i].getScale().y - buttons[i].getSize().y) / 2;
				buttons[i].setPosition({ x,y });

				_canStartMoves[i] = false;
			}

		}
		else {

			if (!_canStartMoves[i]) {
				const float x = buttons[i].getPosition().x + (buttons[i].getSize().x * buttons[i].getScale().x - buttons[i].getSize().x) / 2;
				const float y = buttons[i].getPosition().y + (buttons[i].getSize().y * buttons[i].getScale().y - buttons[i].getSize().y) / 2;
				buttons[i].setPosition({ x,y });

				_canStartMoves[i] = true;
			}

			buttons[i].setScale({ 1,1 });

		}
	}
	
	if (buttons[BUTTONS_START].isPressed())
	{
		response_ = RESPONSES_START;
	}
	else if (buttons[BUTTONS_HIGHSCORES].isPressed())
	{
		response_ = RESPONSES_HIGHSCORES;
	}
	else if (buttons[BUTTONS_SETTINGS].isPressed())
	{
		response_ = RESPONSES_SETTINGS;
	}
	else if (buttons[BUTTONS_EXIT].isPressed())
	{
		response_ = RESPONSES_EXIT;
	}
	else
	{
		response_ = RESPONSES_NONE;
	}

}

void Menu::update() {
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < 4; i++) {
		target.draw(buttons[i]);
	}
}