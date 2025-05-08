#include "display.h"
#include "process.h"
int main(int argc, char* argv[]) {
  int result = -1;
  if (argc != 2) {
    Display::Error();
  } else {
    result = Process::Args(argc, argv);
  }
  return result;
}