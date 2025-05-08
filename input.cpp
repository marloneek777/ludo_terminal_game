#include "input.h"
#include <string>
#include <iostream>
#include <algorithm>

std::string Input::GetProcessedInput() {
  std::string input;
  std::cout << "> ";
  std::getline(std::cin, input);

  //remove whitespaces
  input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

  //cast all chars to lower
  for_each(input.begin(), input.end(), [](char& c) { c = static_cast<char>(::tolower(static_cast<unsigned char>(c))); });

  return input;
}