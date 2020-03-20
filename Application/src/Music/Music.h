#pragma once
#include "NGin.h"

class Music {
public:
	enum Theme {
		Menu = 0,
		Wave,
		GameOver,
		NONE
	};

	static sf::Music nowPlaying_;

	static void playTheme(const Theme theme);

private:
	static Theme iPlaying_;
	static std::vector<std::string> locations_;
};