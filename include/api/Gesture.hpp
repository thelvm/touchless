#ifndef TOUCHLESS_API_GESTURE_HPP
#define TOUCHLESS_API_GESTURE_HPP

#include <vector>
#include <ctime>

#include "json.hpp"
#include "GestureKeyframe.hpp"

namespace touchless {
class Gesture {
 private:
  std::vector<GestureKeyframe> keyframes_;
  unsigned int current_keyframe_number_;
  clock_t last_keyframe_timestamp_;

 public:
  std::string name_;

  /// Distance in mm treshold for two hands to be considered in the same position
  double precision_;

  Gesture();
  void AddKeyframe(const GestureKeyframe &t_keyframe);
  void AddKeyframe(const GestureKeyframe &t_keyframe, unsigned int t_position);
  void RemoveKeyframe();
  void RemoveKeyframe(unsigned int t_position);
  std::optional<touchless::GestureKeyframe> GetKeyframe(unsigned int t_position);
  bool TryHands(const Hands &t_hands);
  nlohmann::json ToJson();
  void FromJson(nlohmann::json j);
  void FromFile(const std::string& json_file_name);
};
} // namespace touchless

#endif //TOUCHLESS_API_GESTURE_HPP
