#include "Music.h"

sf::Music Music::nowPlaying_;
Music::Theme Music::iPlaying_ = Theme::NONE;
std::vector<std::string> Music::locations_ = {
	"assets/menu.wav",
	"assets/wave.wav",
	"assets/gameover.wav"
};

void Music::playTheme(const Theme theme)
{
	if (theme != Theme::NONE) {
		if (theme != iPlaying_) {
			nowPlaying_.openFromFile(locations_[theme]);
			iPlaying_ = theme;
		}

		if (nowPlaying_.getStatus() != sf::Music::Status::Playing) {
			nowPlaying_.play();
		}
	}
	else { // if none
		nowPlaying_.stop();
	}
}
