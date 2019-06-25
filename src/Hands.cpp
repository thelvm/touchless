//
// Created by lucas on 12/06/19.
//

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "Hands.hpp"

touchless::Hands::Hands()
{
    leftHand = nullptr;
    rightHand = nullptr;
}

double touchless::Hands::distanceBetweenHandsX() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_x - rightHand->position_x);
    }
    return -1;
}

double touchless::Hands::distanceBetweenHandsY() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_y - rightHand->position_y);
    }
    return -1;
}

double touchless::Hands::distanceBetweenHandsZ() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return abs(leftHand->position_z - leftHand->position_z);
    }
    return -1;
}

double touchless::Hands::distanceBetweenHands() const
{
    if (leftHand != nullptr && rightHand != nullptr)
    {
        return sqrt(pow((leftHand->position_x - rightHand->position_x), 2) +
                    pow((leftHand->position_y - rightHand->position_y), 2) +
                    pow((leftHand->position_z - rightHand->position_z), 2));
    }
    return -1;
}

bool touchless::Hands::equals(Hands *other, double t_distanceTolerance) const
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

nlohmann::json touchless::Hands::toJSON()
{
    nlohmann::json j;
    if (leftHand != nullptr)
    {
        j["left"] = leftHand->toJSON();
    }
    if (rightHand != nullptr)
    {
        j["right"] = rightHand->toJSON();
    }
    return j;
}

void touchless::Hands::fromJSON(nlohmann::json j)
{
    if (j.find("left") != j.end())
    {
        if (leftHand == nullptr)
        {
            leftHand = new Hand();
        }
        leftHand->fromJSON(j["left"]);
    } else
    {
        delete(leftHand);
        leftHand = nullptr;
    }

    if (j.find("right") != j.end())
    {
        if (rightHand == nullptr)
        {
            rightHand = new Hand();
        }
        rightHand->fromJSON(j["right"]);
    }
    else
    {
        delete(rightHand);
        rightHand = nullptr;
    }
}
