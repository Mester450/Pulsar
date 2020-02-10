#include "Settings.h"
#include "NGin/Levels/MainLevel.h"

void Settings::setup()
{
	// --- Loading Textures ----------------
	buttonTexture_ = ngin::Resources::AcquireTexture("button.png");
	dropdownTexture_ = ngin::Resources::AcquireTexture("dropdown.png");
	sliderTexture_ = ngin::Resources::AcquireTexture("slider.png");
	confirmDialogTexture_ = ngin::Resources::AcquireTexture("confirm_dialog.png");
	font_ = ngin::Resources::AcquireFont("pixeled.ttf");
	// -------------------------------------

	// --- Setting Textures ----------------
	backButton_.setTexture(*buttonTexture_);
	applyButton_.setTexture(*buttonTexture_);
	soundSlider_.setTexture(*sliderTexture_);
	musicSlider_.setTexture(*sliderTexture_);
	videoModeDropdown_.setTexture(*dropdownTexture_);
	windowTypeDropdown_.setTexture(*dropdownTexture_);
	confirmDialog_.setTextures(*confirmDialogTexture_, *buttonTexture_);
	// -------------------------------------

	// --- Setting Styles ------------------
	setupUIStyle(*font_, 40, sf::Color{ 28, 105, 214 }, sf::Color{ 214, 112, 28 });
	// -------------------------------------

	// --- Setting Scales ------------------
	soundSlider_.setScale({ 1.2F, 1.2F });
	musicSlider_.setScale({ 1.2F, 1.2F });
	// -------------------------------------

	// --- Other Properties ----------------
	soundSlider_.setLevel(ngin::Audio::getSoundVolume());
	soundText_.setString("Sound Volume");
	musicSlider_.setLevel(ngin::Audio::getMusicVolume());
	musicText_.setString("Music Volume");

	confirmDialog_.setString("Are you sure you want to keep these changes?");

	windowModeText_.setString("Window Mode");
	windowTypeDropdown_.addDropString("Windowed");
	windowTypeDropdown_.addDropString("Borderless");
	windowTypeDropdown_.addDropString("Fullscreen");
	/*windowModeDropdown_ drop nr 0 set in getFromWindow()*/

	resolutionText_.setString("Resolution");
	addResolutionsTo(videoModeDropdown_);
	/*resolutionDropdown_ drop nr 0 set in getFromWindow()*/
	// -------------------------------------

	// --- Setting Positions ---------------
	backButton_.setPosition({ 105, 965 });
	applyButton_.setPosition({ 735, 965 });
	soundSlider_.setPosition({ 425, 450 });
	musicSlider_.setPosition({ 425, 600 });
	windowTypeDropdown_.setPosition({ 1000, 600 });
	videoModeDropdown_.setPosition({ 1300, 450 });

	confirmDialog_.setPosition({ 960 - confirmDialog_.getGlobalBounds().width / 2,
								 540 - confirmDialog_.getGlobalBounds().height / 2 });
	confirmDialog_.setTextOffset(-40.0F);

	ngin::centerTextInBounds(soundText_, soundSlider_.getGlobalBounds(), -47);
	ngin::centerTextInBounds(musicText_, musicSlider_.getGlobalBounds(), -47);
	ngin::centerTextInBounds(windowModeText_, windowTypeDropdown_.getClosedGlobalBounds(), -45);
	ngin::centerTextInBounds(resolutionText_, videoModeDropdown_.getClosedGlobalBounds(), -45);
	// -------------------------------------

	// --- Getting Data --------------------
	if (ngin::MainLevel::windowType_ == ngin::WINDOW_TYPE::WINDOW_UNRESIZEABLE)
		windowTypeDropdown_.setActiveDrop(1); // windowed
	else if (ngin::MainLevel::windowType_ == ngin::WINDOW_TYPE::WINDOW_BORDERLESS)
		windowTypeDropdown_.setActiveDrop(2); // borderless
	else if (ngin::MainLevel::windowType_ == ngin::WINDOW_TYPE::WINDOW_FULLSCREEN)
		windowTypeDropdown_.setActiveDrop(3); // fullscreen
	else if (ngin::MainLevel::windowType_ == ngin::WINDOW_TYPE::WINDOW_RESIZEABLE)
		NG_LOG_ERROR("Window has unsupported Type!"); /// !!! Resizeable window is considered error

	std::string resolutionString =
		std::to_string(ngin::MainLevel::windowVideoMode_.width)
		+ " x " +
		std::to_string(ngin::MainLevel::windowVideoMode_.height);

	videoModeDropdown_.setDropString(0, resolutionString);

	saveWindowTypeString_ = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];
	saveVideoMode_ = ngin::MainLevel::windowVideoMode_;
	// -------------------------------------
}

void Settings::handleEvents(const sf::Event& event)
{
	// default response and changeType
	response_ = RESPONSES::RESPONSES_NONE;

	if (dialogActive_)
	{
		confirmDialog_.handleEvents(event, ngin::Cursor::getPosition());

		if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::OK ||
			confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::CLOSE)
		{
			// OK pressed => make changes permanent
			if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::OK)
				changeType_ = CHANGE::CHANGE_PERMANENT;
			// CLOSE pressed => reset changes
			else if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::CLOSE)
				changeType_ = CHANGE::CHANGE_REVERT;
			else
				changeType_ = CHANGE::CHANGE_NONE;
		}
	}
	else
	{
		applyButton_.handleEvents(event, ngin::Cursor::getPosition());
		backButton_.handleEvents(event, ngin::Cursor::getPosition());
		soundSlider_.handleEvents(event, ngin::Cursor::getPosition());
		musicSlider_.handleEvents(event, ngin::Cursor::getPosition());
		windowTypeDropdown_.handleEvents(event, ngin::Cursor::getPosition());
		videoModeDropdown_.handleEvents(event, ngin::Cursor::getPosition());

		ngin::Audio::setSoundVolume(soundSlider_.getLevel());
		ngin::Audio::setMusicVolume(musicSlider_.getLevel());

		// fullscreen supports only one resolution
		if (windowTypeDropdown_.getActiveDrop() == 3) {
			videoModeDropdown_.setActiveDrop(1);
			videoModeDropdown_.setDisabled(true);
		}
		else {
			videoModeDropdown_.setDisabled(false);
		}

		if (applyButton_.isActive())
			changeType_ = CHANGE::CHANGE_TEMPORARY;
		else
			changeType_ = CHANGE::CHANGE_NONE;

		if (backButton_.isActive())
			response_ = RESPONSES::RESPONSES_MENU;
	}
}

void Settings::update()
{
	if (dialogActive_) {
		resetTimer_ += ngin::Timer::getDeltaTime();
		int secsRemaining = static_cast<int>(resetLimit_ - resetTimer_);

		std::string confirmDialogString = "Are you sure you want to keep these changes?\n"
			"                    Reverting in " + std::to_string(secsRemaining) + " seconds";

		confirmDialog_.setString(confirmDialogString);

		if (secsRemaining == 0)
			changeType_ = CHANGE::CHANGE_REVERT; // type of change
	}

	if (changeType_ != CHANGE::CHANGE_NONE) {
		applySettingsToWindow();
	}
}

void Settings::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(soundSlider_);
	target.draw(soundText_);

	target.draw(musicSlider_);
	target.draw(musicText_);

	target.draw(backButton_);
	target.draw(applyButton_);

	target.draw(windowTypeDropdown_);
	target.draw(windowModeText_);

	target.draw(videoModeDropdown_);
	target.draw(resolutionText_);

	if (dialogActive_)
		target.draw(confirmDialog_);
}

void Settings::applySettingsToWindow()
{
	sf::VideoMode videoMode;
	std::string windowTypeString;

	// --- Change based on changeType_ ------------------------------------------
	if (changeType_ == CHANGE::CHANGE_REVERT)
	{
		videoMode = saveVideoMode_;
		windowTypeString = saveWindowTypeString_;
		dialogActive_ = false; // close dialog
	}
	else if (changeType_ == CHANGE::CHANGE_PERMANENT)
	{
		// PERMANENT always runs after TEMPORARY -> very important !
		saveVideoMode_ = ngin::MainLevel::windowVideoMode_;
		saveWindowTypeString_ = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];

		videoMode = ngin::MainLevel::windowVideoMode_;
		windowTypeString = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];
		dialogActive_ = false; // close dialog
	}
	else if (changeType_ == CHANGE::CHANGE_TEMPORARY)
	{
		windowTypeString = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];

		if (windowTypeString == windowTypeStrings_[2])
			videoMode = sf::VideoMode::getDesktopMode(); // fullscreen resolution
		else if (videoModeDropdown_.getActiveDrop() != 0)  // if dropdown has one drop selected
			videoMode = videoModes_[videoModeDropdown_.getActiveDrop() - 1]; // apply selected
		else
			videoMode = ngin::MainLevel::windowVideoMode_; // else use default
	}
	// --------------------------------------------------------------------------

	// --- Apply changes internally and externally ------------------------------
	// check if there is need for a dialog box
	auto tempType = ngin::MainLevel::windowType_;
	auto tempVideoMode = ngin::MainLevel::windowVideoMode_;

	if (windowTypeString == windowTypeStrings_[0]) // windowed
	{
		ngin::MainLevel::windowType_ = ngin::WINDOW_TYPE::WINDOW_UNRESIZEABLE;
		windowTypeDropdown_.setActiveDrop(1);
	}
	else if (windowTypeString == windowTypeStrings_[1]) // borderless
	{
		ngin::MainLevel::windowType_ = ngin::WINDOW_TYPE::WINDOW_BORDERLESS;
		windowTypeDropdown_.setActiveDrop(2);
	}
	else if (windowTypeString == windowTypeStrings_[2]) // fullscreen
	{
		ngin::MainLevel::windowType_ = ngin::WINDOW_TYPE::WINDOW_FULLSCREEN;
		windowTypeDropdown_.setActiveDrop(3);
	}

	ngin::MainLevel::windowVideoMode_ = videoMode;

	std::string resolutionString =
		std::to_string(videoMode.width) + " x " + std::to_string(videoMode.height);

	videoModeDropdown_.setDropString(0, resolutionString);

	// only start dialog if changes have been made
	if (changeType_ == CHANGE::CHANGE_TEMPORARY &&
		(tempType != ngin::MainLevel::windowType_ ||
		 tempVideoMode != ngin::MainLevel::windowVideoMode_)) {
		dialogActive_ = true; // open dialog
		resetTimer_ = 0; // start resetTimer_ from 0
	}
	// --------------------------------------------------------------------------
}

void Settings::addResolutionsTo(ngin::Dropdown& dropdown)
{
	videoModes_.clear(); // clear resolution vector
	std::vector<sf::Vector2i> importantResolutions_ = {
	{1920, 1080},
	{1366, 768},
	{1360, 768},
	{1280, 800},
	{800, 600} };
	
	// important + FullScreenModes ( 5 + 7(max)) = 12MAX DROPDOWNS
	std::vector<sf::VideoMode> fullScreenModes_ = sf::VideoMode::getFullscreenModes();

	for (int i = 0; i < int(fullScreenModes_.size()); i++) {
		std::string resolutionString =
			std::to_string(fullScreenModes_[i].width) + " x " + std::to_string(fullScreenModes_[i].height);

		bool isImportant = false;
		for (int j = 0; j < int(importantResolutions_.size()); j++) {
			if (importantResolutions_[j].x == fullScreenModes_[i].width &&
				importantResolutions_[j].y == fullScreenModes_[i].height) {
				isImportant = true;
				break;
			}
		}

		if (i <= 7 || isImportant) {
			videoModes_.push_back(fullScreenModes_[i]);
			dropdown.addDropString(resolutionString);
		}
	}
}

void Settings::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& backgroundColor, const sf::Color& fontColor)
{
	backButton_.setFont(font);
	backButton_.setCharacterSize(fontSize);
	backButton_.setSelectColor(fontColor);
	backButton_.setTextColor(fontColor);

	applyButton_.setFont(font);
	applyButton_.setCharacterSize(fontSize);
	applyButton_.setSelectColor(fontColor);
	applyButton_.setTextColor(fontColor);

	soundSlider_.setSelectThickness(2.5F);
	soundSlider_.setSelectColor(fontColor);

	soundText_.setFont(font);
	soundText_.setFillColor(fontColor);
	soundText_.setCharacterSize(fontSize);

	musicSlider_.setSelectThickness(2.5F);
	musicSlider_.setSelectColor(fontColor);

	musicText_.setFont(font);
	musicText_.setFillColor(fontColor);
	musicText_.setCharacterSize(fontSize);

	windowTypeDropdown_.setFont(font);
	windowTypeDropdown_.setSelectColor(fontColor);
	windowTypeDropdown_.setTextColor(fontColor);
	windowTypeDropdown_.setCharacterSize(fontSize);
	windowTypeDropdown_.setHighlightColor({ fontColor.r, fontColor.g, fontColor.b, 80 });

	videoModeDropdown_.setFont(font);
	videoModeDropdown_.setSelectColor(fontColor);
	videoModeDropdown_.setTextColor(fontColor);
	videoModeDropdown_.setCharacterSize(fontSize);
	videoModeDropdown_.setHighlightColor({ fontColor.r, fontColor.g, fontColor.b, 80 });

	windowModeText_.setFont(font);
	windowModeText_.setFillColor(fontColor);
	windowModeText_.setCharacterSize(fontSize);

	resolutionText_.setFont(font);
	resolutionText_.setFillColor(fontColor);
	resolutionText_.setCharacterSize(fontSize);

	confirmDialog_.setFont(font);
	confirmDialog_.setTextColor(fontColor);
	confirmDialog_.setButtonsCharacterSize(fontSize - 2);
	confirmDialog_.setTextCharacterSize(fontSize + 7);
	confirmDialog_.setSelectColor(fontColor);

	backButton_.setFillColor(backgroundColor);
	applyButton_.setFillColor(backgroundColor);
	soundSlider_.setFillColor(backgroundColor);
	musicSlider_.setFillColor(backgroundColor);
	windowTypeDropdown_.setFillColor(backgroundColor);
	videoModeDropdown_.setFillColor(backgroundColor);
}
