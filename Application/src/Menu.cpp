#include "Menu.h"

void Menu::setup() {
	for (int i = 0; i < 4; i++) {
		buttons[i].setTexture(*ngin::Resources::AcquireTexture("button.png"));
		buttons[i].setFont(*ngin::Resources::AcquireFont("pixeled.ttf"));
		buttonScales[i] = { 1.20F, 1.20F };
		buttons[i].setScale(buttonScales[i]);
		buttonPositions[i] = { ngin::MainLevel::view_.getSize().x / 2 - buttons[i].getGlobalBounds().width / 2,
			300 + static_cast<float>(i) * 100 };
		buttons[i].setPosition(buttonPositions[i]);
		buttons[i].setSelectThickness(0);
		buttons[i].setFillColor({ 28, 105, 214 });
		buttons[i].setTextColor({ 214, 112, 28 });
	}
}

void Menu::handleEvents(const sf::Event& event)
{

	for (int i = 0; i < 4; i++) {

		buttons[i].handleEvents(event, ngin::Cursor::getPosition());

		sf::Vector2f scaleAbove = { 1.22f,1.22f };
		if (buttons[i].isSelected()) {

			if (_canStartMoves[i]) {
				const float x = buttonPositions[i].x - (buttons[i].getSize().x * scaleAbove.x - buttons[i].getSize().x * buttonScales[i].x) / 2;
				const float y = buttonPositions[i].y - (buttons[i].getSize().y * scaleAbove.y - buttons[i].getSize().y * buttonScales[i].y) / 2;
				buttons[i].setPosition({ x,y });

				_canStartMoves[i] = false;
			}

			buttons[i].setScale(scaleAbove);
		}
		else {
			if (!_canStartMoves[i]) {
				const float x = buttonPositions[i].x;
				const float y = buttonPositions[i].y;
				buttons[i].setPosition({ x,y });

				_canStartMoves[i] = true;
			}

			buttons[i].setScale(buttonScales[i]);
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