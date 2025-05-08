#include "display.h"
#include "ludo.h"
#include <iostream>
#include <string>
#include <vector>
void Display::Error() {
	std::cout
		<< "Ooops! Something went wrong...\n"
		<< "Type -help after the executable name to show possible actions\n"
		<< "(eg. \"./executable -help\" or \"-h\" for short)\n";
}

void Display::AvailableCommands() {
	std::cout
		<< "Available actions: \"-ludo\", \"-help\"";
}

void Display::string(std::string s) {
	std::cout
		<< s << '\n';
}

void Display::Ludo::Rules() {
	std::cout
		<< "Welcome to Ludo!\n"
		<< "-------------------------------------------\n"
		<< "There shoudl be some rules here or smth....\n";
}

void Display::Ludo::Board() { // temporarly
	std::cout
		<< "-------------------\n"
		<< "--------------------\n"
		<< "--------------------\n"
		<< "--------------------\n";
}

void Display::Ludo::Commands() {
	std::cout
		<< "Type -roll to roll, -pass to pass your turn\n";
}

void Display::Ludo::Roll(int roll, int current_player) {
	std::cout
		<< current_player << " rolled: " << roll << '\n';
}