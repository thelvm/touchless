//
// Created by lucas on 12/06/19.
//

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "ParsedHands.hpp"

gesture_parser::ParsedHands::ParsedHands()
{
    leftHand = nullptr;
    rightHand = nullptr;
}

double gesture_parser::ParsedHands::getXDistance() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_x - rightHand->position_x);
    }
    return -1;
}

double gesture_parser::ParsedHands::getYDistance() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_y - rightHand->position_y);
    }
    return -1;
}

double gesture_parser::ParsedHands::getZDistance() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_z - leftHand->position_z);
    }
    return -1;
}

double gesture_parser::ParsedHands::getDistance() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return sqrt(pow((leftHand->position_x - rightHand->position_x), 2) +
                    pow((leftHand->position_y - rightHand->position_y), 2) +
                    pow((leftHand->position_z - rightHand->position_z), 2));
    }
    return -1;
}

bool gesture_parser::ParsedHands::equals(const gesture_parser::ParsedHands &other, double t_distanceTolerance) const
{
    double distanceTolerance = t_distanceTolerance / 2;
    return leftHand == other.leftHand &&
           rightHand == other.rightHand &&

           (other.getXDistance() - distanceTolerance) < getXDistance() &&
           getXDistance() < (other.getXDistance() + distanceTolerance) &&

           (other.getYDistance() - distanceTolerance) < getYDistance() &&
           getYDistance() < (other.getYDistance() + distanceTolerance) &&

           (other.getZDistance() - distanceTolerance) < getZDistance() &&
           getZDistance() < (other.getZDistance() + distanceTolerance);
}
