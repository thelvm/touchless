//
// Created by lucas on 12/06/19.
//

#include "GestureKeyframe.hpp"

gesture_parser::GestureKeyframe::GestureKeyframe() = default;

gesture_parser::GestureKeyframe::GestureKeyframe(const nlohmann::json &t_json)
{
    nlohmann::json leftHandJSON = t_json["left_hand"];
    nlohmann::json rightHandJSON = t_json["right_hand"];
}
