#pragma once
#include "NGin.h"

#include "Settings/ConfirmDialog.h"
#include <fstream>

class Settings : public ngin::Level {
public:
	void setup();
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void applySettingsToWindow();

	enum RESPONSES {
		RESPONSES_NONE = 14,
		RESPONSES_MENU
	};
private:
	void setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& backgroundColor, const sf::Color& fontColor);
	void addResolutionsTo(ngin::Dropdown& dropdown);

	bool writeFile(); // false if error
	bool readFile(); // false if error

	// Navigation buttons 
	ngin::Button backButton_{ "Back", {400, 50} };
	ngin::Button applyButton_{ "Apply", {400, 50} };

	// Settings UI
	ngin::Slider soundSlider_{ {300, 40}, {40, 40}, {30, 30} };
	ngin::Slider musicSlider_{ {300, 40}, {40, 40}, {30, 30} };

	ngin::Dropdown windowTypeDropdown_{ { 300, 40 } };
	ngin::Dropdown videoModeDropdown_{ { 300, 40 } };

	// Confirm Dialog
	ConfirmDialog confirmDialog_;
	
	float resetTimer_ = 0.0F;
	const float resetLimit_ = 10.0F;

	bool dialogActive_ = false;
	bool applyChanges_ = false;
	enum class CHANGE {
		CHANGE_NONE,
		CHANGE_TEMPORARY,
		CHANGE_PERMANENT,
		CHANGE_REVERT
	} changeType_;

	// Properties
	sf::VideoMode saveVideoMode_;
	std::string saveWindowTypeString_;

	std::vector<std::string> windowTypeStrings_ {
		"Windowed",
		"Borderless",
		"Fullscreen"
	};
	std::vector<sf::VideoMode> videoModes_; // constructed in addResolutionsTo()

	// Static stuff
	sf::Text soundText_;
	sf::Text musicText_;
	sf::Text windowModeText_;
	sf::Text resolutionText_;

	// Textures
	std::shared_ptr<sf::Font> font_;
	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Texture> dropdownTexture_;
	std::shared_ptr<sf::Texture> sliderTexture_;
	std::shared_ptr<sf::Texture> confirmDialogTexture_;

	// reading and writing
	std::string fileName_ = "settings.txt";
};