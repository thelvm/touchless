//
// Created by lucas on 12/06/19.
//

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "Hands.hpp"

gesture_parser::Hands::Hands()
{
    leftHand = nullptr;
    rightHand = nullptr;
}

double gesture_parser::Hands::distanceBetweenHandsX() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_x - rightHand->position_x);
    }
    return -1;
}

double gesture_parser::Hands::distanceBetweenHandsY() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_y - rightHand->position_y);
    }
    return -1;
}

double gesture_parser::Hands::distanceBetweenHandsZ() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_z - leftHand->position_z);
    }
    return -1;
}

double gesture_parser::Hands::distanceBetweenHands() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return sqrt(pow((leftHand->position_x - rightHand->position_x), 2) +
                    pow((leftHand->position_y - rightHand->position_y), 2) +
                    pow((leftHand->position_z - rightHand->position_z), 2));
    }
    return -1;
}

bool gesture_parser::Hands::equals(Hands *other, double t_distanceTolerance) const
{
    double distanceTolerance = t_distanceTolerance / 2;
    return leftHand == other->leftHand &&
           rightHand == other->rightHand &&

           (other->distanceBetweenHandsX() - distanceTolerance) < distanceBetweenHandsX() &&
           (other->distanceBetweenHandsX() + distanceTolerance) > distanceBetweenHandsX() &&

           (other->distanceBetweenHandsY() - distanceTolerance) < distanceBetweenHandsY() &&
           (other->distanceBetweenHandsY() + distanceTolerance) > distanceBetweenHandsY() &&

           (other->distanceBetweenHandsZ() - distanceTolerance) < distanceBetweenHandsZ() &&
           (other->distanceBetweenHandsZ() + distanceTolerance) > distanceBetweenHandsZ();
}
