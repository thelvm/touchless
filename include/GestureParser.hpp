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

  using OnGestureCallbackT = std::function<void(const std::string&)>;
  using OnCanParseGesturesT = std::function<void()>;
  using OnCannotParseGesturesT = std::function<void()>;
  OnGestureCallbackT on_gesture_callback_;
  OnCannotParseGesturesT on_cannot_parse_gestures_callback_;
  OnCanParseGesturesT on_can_parse_gestures_callback_;

  /// Parses hands to detect gestures.
  /// If a gesture is detected, calls onGesture on the listener
  void AnalyseHands(const Hands &hands);
  void OnCanParseGestures();
  void OnCannotParseGestures();
 public:
  GestureParser();
  /// Starts attempting to connect to the Leap Motion Sensor.
  /// Once it is successful, starts processing the Leap Motion Sensor input.
  void Start();
  /// Stops all processing and disconnects from the Leap Motion Sensor.
  void Stop();
  /// Adds a gesture to the list of gestures to detect
  void AddOrReplaceGesture(const Gesture &t_gesture);
  /// Removes a Gesture with corresponding name from the list of gestures to detect
  void RemoveGesture(const std::string &gesture_name);
  void LoadGesturesFromDir(const std::string &dir_path);
  void SetOnGestureCallback(OnGestureCallbackT gesture_callback);
  void SetOnCanParseGesturesCallback(OnCanParseGesturesT callback);
  void SetOnCannotParseGesturesCallback(OnCannotParseGesturesT callback);
};
} // namespace touchless

#endif