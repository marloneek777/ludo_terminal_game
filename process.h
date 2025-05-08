#pragma once
namespace Process {
  enum class program_state { LUDO, INVALID, GET_HELP };
  int Args(int argc, char* argv[]);
}