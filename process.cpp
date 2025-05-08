#include <algorithm>
#include <cctype>
#include "process.h"
#include "string_utils.h"
#include "display.h"
#include "ludo.h"
int Process::Args(int argc,char* argv[]) {
  argc;// 
  int result = -1;
  program_state state{ program_state::INVALID };

  std::string wows = Utils::removeWhitespace(argv[1]);
  std::for_each(wows.begin(), wows.end(), [](char& c) { c = static_cast<char>(::tolower(static_cast<unsigned char>(c))); });
  
  if (wows == "-ludo" || wows == "-l") {
    state = program_state::LUDO;
  }
  else if (wows == "-help" || wows == "-h") {
    state = program_state::GET_HELP;
  }
  else {
    state = program_state::INVALID;
  }

  switch (state) {
  case program_state::INVALID:
    Display::Error();
    break;
  case program_state::GET_HELP:
    Display::AvailableCommands();
    result = 0;
    break;
  case program_state::LUDO:
    result = Ludo::GameManager();
    break;
  default:
    break;
  }
  return result;
}