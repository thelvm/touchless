#include <string>

#include "commands.hpp"

using namespace touchless::gesture_manager;

int main(int argc, char **argv) {
  if (argc == 1) {
    return DisplayBasicHelp();
  }

  std::string command = argv[1];
  if (command == "add") {
    return AddGesture(argc, argv);
  } else if (command == "remove") {
    return RemoveGesture(argc, argv);
  } else if (command == "edit") {
    return EditGesture(argc, argv);
  } else if (command == "list") {
    return ListGestures();
  } else {
    return DisplayBasicHelp();
  }
}