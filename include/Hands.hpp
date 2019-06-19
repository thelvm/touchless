//
// Created by lucas on 12/06/19.
//

#ifndef GESTURE_PARSER_API_HANDS_HPP
#define GESTURE_PARSER_API_HANDS_HPP

#include "Hand.hpp"

namespace gesture_parser
{
class Hands
{
public:
    Hand *leftHand;
    Hand *rightHand;

    Hands();

    bool equals(Hands *other, double t_distanceTolerance) const;

    double distanceBetweenHandsX() const;

    double distanceBetweenHandsY() const;

    double distanceBetweenHandsZ() const;

    double distanceBetweenHands() const;
};
} // namespace gesture_parser

#endif //GESTURE_PARSER_API_HandS_HPP
