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

nlohmann::json touchless::GestureKeyframe::toJSON()
{
    nlohmann::json j;

    if (hands != nullptr)
    {
        j["hands"] = hands->toJSON();
    }
    j["minDelay"] = minDelay;
    j["maxDelay"] = maxDelay;
    j["leftDeltaX"] = leftDeltaX;
    j["leftDeltaY"] = leftDeltaY;
    j["leftDeltaZ"] = leftDeltaZ;
    j["rightDeltaX"] = rightDeltaX;
    j["rightDeltaY"] = rightDeltaY;
    j["rightDeltaZ"] = rightDeltaZ;

    return j;
}

void touchless::GestureKeyframe::fromJSON(nlohmann::json j)
{
    if (j.find("hands") != j.end())
    {
        if (hands == nullptr) {
            hands = new Hands();
        }
        hands->fromJSON(j["hands"]);
    }
    else
    {
        delete(hands);
        hands = nullptr;
    }

    minDelay = j["minDelay"];
    maxDelay = j["maxDelay"];
    leftDeltaX = j["leftDeltaX"];
    leftDeltaY = j["leftDeltaY"];
    leftDeltaZ = j["leftDeltaZ"];
    rightDeltaX = j["rightDeltaX"];
    rightDeltaY = j["rightDeltaY"];
    rightDeltaZ = j["rightDeltaZ"];
}
