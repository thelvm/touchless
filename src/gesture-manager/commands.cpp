#include <iostream>
#include <filesystem>
#include <thread>
#include <fstream>

#include "touchless.hpp"
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
  if (!touchless::IsLeapDaemonRunning()) {
    std::cerr << "Leap daemon (leapd) not running or no sensor available." << std::endl;
    return 1;
  }
  touchless::HandsParser hands_parser;
  touchless::Gesture gesture;
  char answer = 'y';
  while (answer == 'y') {
    std::cout << "Press enter when you're ready to add a keyframe" << std::endl;
    std::cin.ignore();
    std::cout << "Hold hands in position for a few seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::optional<touchless::Hands> hands;
    hands = hands_parser.GetHands();
    touchless::GestureKeyframe keyframe;
    keyframe.hands_ = hands.value_or(touchless::Hands());
    gesture.AddKeyframe(keyframe);

    std::cout << "Add another keyframe? (y, n)" << std::endl;
    std::cin >> answer;
  }
  std::cout << "Enter name for the gesture" << std::endl;
  std::string name;
  std::cin >> name;
  gesture.name_ = name;

  using namespace std::filesystem;
  std::string home_dir = getenv("HOME");
  auto gestures_dir = path(home_dir + "/.touchless/gestures");
  if (!exists(gestures_dir)) {
    create_directories(gestures_dir);
  }
  std::ofstream out_file;
  out_file.open(gestures_dir.generic_string() + "/" + gesture.name_ + ".gesture", std::iostream::out);
  out_file << gesture.ToJson();

  std::cout << "Gesture saved" << std::endl;
  out_file.close();
  return 0;
}

int touchless::gesture_manager::EditGesture(int argc, char **argv) {
  std::cout << "No implemented yet." << std::endl;
  return 0;
}

int touchless::gesture_manager::RemoveGesture(int argc, char **argv) {
  return 0;
}

int touchless::gesture_manager::ListGestures() {
  using namespace std::filesystem;
  std::string home_dir = getenv("HOME");
  auto gestures_dir = path(home_dir + "/.touchless/gestures");
  if (!exists(gestures_dir) || is_empty(gestures_dir)) {
    std::cout
        << "No gestures found." << std::endl
        << "Create a new one by typing 'gesture-manager add' or copy gesture files to " << gestures_dir << std::endl;
    return 1;
  }

  for (auto &entry : directory_iterator(gestures_dir)) {
    if (is_regular_file(entry)) {
      if (entry.path().extension() == ".gesture") {
        try {
          touchless::Gesture gesture;
          gesture.FromFile(entry.path());
          std::cout << gesture.name_ << std::endl;
        } catch (...) {
          std::cout << entry.path().filename() << " isn't a valid gesture file." << std::endl;
        }
      }
    }
  }
  return 0;
}
