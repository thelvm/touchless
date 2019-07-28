#ifndef TOUCHLESS_API_GESTURE_PARSER
#define TOUCHLESS_API_GESTURE_PARSER

#include <map>
#include <functional>

#include "Gesture.hpp"
#include "HandsParser.hpp"

namespace touchless {
/// Main parser class. Parses Gesture from a list directly from the Leap Motion Sensor
class GestureParser {
 private:
  /// Hands parser used in gesture detection
  std::unique_ptr<HandsParser> hands_parser_;
  /// The list of gestures to detect
  std::map<std::string, Gesture> gestures_list_;
  /// Parses hands to detect gestures.
  /// If a gesture is detected, calls onGesture on the listener
  void ParseHands(const Hands &parsed_hands);
 public:
  GestureParser();
  /// Starts attempting to connect to the Leap Motion Sensor.
  /// Once it is successful, starts processing the Leap Motion Sensor input.
  void Start();
  /// Stops all processing and disconnects from the Leap Motion Sensor.
  void Stop();
  /// Adds a gesture to the list of gestures to detect
  void AddOrReplaceGesture(Gesture *t_gesture);
  /// Removes a Gesture with corresponding name from the list of gestures to detect
  void RemoveGesture(char *gesture_name);
  void OnCanParseHands();
  void OnCannotParseHands();
  void OnHands(const Hands &t_hands);
  void LoadGesturesFromDir(const std::string& dir_path);
};
} // namespace touchless

#endif