#include <iostream>
#include <filesystem>

#include "commands.hpp"

int touchless::gesture_manager::DisplayBasicHelp() {
  std::cout << "Usage: gesture-manager command" << std::endl;
  std::cout << std::endl;
  std::cout << "Command list:" << std::endl;
  std::cout << "\tadd - add gesture" << std::endl;
  std::cout << "\tremove - remove existing gesture" << std::endl;
  std::cout << "\tedit - edit existing gesture" << std::endl;
  std::cout << "\ttest - test existing gestures" << std::endl;
  std::cout << "\tlist - lists existing gestures" << std::endl;
  return 0;
}

int touchless::gesture_manager::AddGesture(int argc, char **argv) {
  return 0;
}

int touchless::gesture_manager::EditGesture(int argc, char **argv) {
  return 0;
}

int touchless::gesture_manager::RemoveGesture(int argc, char **argv) {
  return 0;
}

int touchless::gesture_manager::ListGestures() {
  using namespace std::filesystem;
  std::string home_dir = getenv("HOME");
  auto gestures_dir = canonical(home_dir + "/.touchless/gestures");
  if (!exists(gestures_dir) || is_empty(gestures_dir)) {
    std::cout
        << "No gestures found." << std::endl
        << "Create a new one by typing 'gesture-manager add' or copy gesture files to " << gestures_dir << std::endl;
    return 1;
  }

  for(auto &file : gestures_dir) {
    if (is_regular_file(file)) {
      std::cout << "That's a file" << std::endl;
    }
  }
  return 0;
}
