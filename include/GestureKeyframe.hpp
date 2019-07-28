//
// Created by lucas on 12/06/19.
//

#ifndef TOUCHLESS_API_GESTUREKEYFRAME_HPP
#define TOUCHLESS_API_GESTUREKEYFRAME_HPP

#include <ctime>
#include "Hands.hpp"
#include "json.hpp"

namespace touchless {
class GestureKeyframe {
 public:
  Hands hands_;
  static double position_precision_;

  /// Maximum delay in seconds since the previous keyframe
  unsigned int max_delay_;

  /// Minimum delay in seconds since the previous keyframe
  unsigned int min_delay_;

  /// Distance the left needs to have moved
  double left_delta_x_;
  double left_delta_y_;
  double left_delta_z_;

  /// Distance the right needs to have moved
  double right_delta_x_;
  double right_delta_y_;
  double right_delta_z_;

  GestureKeyframe();
  explicit GestureKeyframe(const nlohmann::json &json);
  bool Compare(const Hands &t_hands, double t_precision);
  [[nodiscard]] nlohmann::json ToJson();
  void FromJson(nlohmann::json j);
};
} // namespace touchless

#endif //TOUCHLESS_API_GESTUREKEYFRAME_HPP
