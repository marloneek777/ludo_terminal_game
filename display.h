#pragma once
#include <string>
#include <vector>
#include "ludo.h"
namespace Display {
	void Error();
	void string(std::string s);
	void AvailableCommands();

	namespace Ludo {
		void Roll(int roll, int current_player);
		void Commands();
		void Rules();
		void Board();
	}
}

