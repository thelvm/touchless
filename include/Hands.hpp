//
// Created by lucas on 12/06/19.
//

#ifndef TOUCHLESS_API_HANDS_HPP
#define TOUCHLESS_API_HANDS_HPP

#include "Hand.hpp"

namespace touchless
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
} // namespace touchless

#endif //TOUCHLESS_API_HandS_HPP
