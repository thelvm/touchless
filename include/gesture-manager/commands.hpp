#ifndef TOUCHLESS_INCLUDE_GESTURE_MANAGER_COMMANDS_HPP_
#define TOUCHLESS_INCLUDE_GESTURE_MANAGER_COMMANDS_HPP_

namespace touchless::gesture_manager {
int DisplayBasicHelp();
int AddGesture(int argc, char **argv);
int EditGesture(int argc, char **argv);
int RemoveGesture(int argc, char **argv);
int ListGestures();
}

#endif //TOUCHLESS_INCLUDE_GESTURE_MANAGER_COMMANDS_HPP_
