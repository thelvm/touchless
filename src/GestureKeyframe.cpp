//
// Created by lucas on 12/06/19.
//

#include "GestureKeyframe.hpp"

touchless::GestureKeyframe::GestureKeyframe()
{
    hands = nullptr;
    minDelay = 0;
    maxDelay = 5000;
    leftDeltaX = 0.0;
    leftDeltaY = 0.0;
    leftDeltaZ = 0.0;
    rightDeltaX = 0.0;
    rightDeltaY = 0.0;
    rightDeltaZ = 0.0;
}

touchless::GestureKeyframe::GestureKeyframe(const nlohmann::json &t_json)
{
    nlohmann::json leftHandJSON = t_json["left_hand"];
    nlohmann::json rightHandJSON = t_json["right_hand"];
}

bool touchless::GestureKeyframe::compare(Hands *t_hands, double t_precision)
{
    return hands->equals(t_hands, t_precision);
}
