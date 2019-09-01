//
// Created by lucas on 12/06/19.
//

#include "GestureKeyframe.hpp"

touchless::GestureKeyframe::GestureKeyframe() {
  min_delay_ = 0;
  max_delay_ = 5000;
  left_delta_x_ = 0.0;
  left_delta_y_ = 0.0;
  left_delta_z_ = 0.0;
  right_delta_x_ = 0.0;
  right_delta_y_ = 0.0;
  right_delta_z_ = 0.0;
}

touchless::GestureKeyframe::GestureKeyframe(const nlohmann::json &json) {
  FromJson(json);
}

bool touchless::GestureKeyframe::Compare(const Hands &t_hands, double t_precision) {
  return hands_.Equals(t_hands, t_precision);
}

nlohmann::json touchless::GestureKeyframe::ToJson() {
  nlohmann::json j;

  j["hands"] = hands_.ToJson();
  j["min_delay_"] = min_delay_;
  j["max_delay_"] = max_delay_;
  j["left_delta_x_"] = left_delta_x_;
  j["left_delta_y_"] = left_delta_y_;
  j["left_delta_z_"] = left_delta_z_;
  j["right_delta_x_"] = right_delta_x_;
  j["right_delta_y_"] = right_delta_y_;
  j["right_delta_z_"] = right_delta_z_;

  return j;
}

void touchless::GestureKeyframe::FromJson(nlohmann::json j) {
  hands_.FromJson(j["hands"]);
  min_delay_ = j["min_delay_"];
  max_delay_ = j["max_delay_"];
  left_delta_x_ = j["left_delta_x_"];
  left_delta_y_ = j["left_delta_y_"];
  left_delta_z_ = j["left_delta_z_"];
  right_delta_x_ = j["right_delta_x_"];
  right_delta_y_ = j["right_delta_y_"];
  right_delta_z_ = j["right_delta_z_"];
}
