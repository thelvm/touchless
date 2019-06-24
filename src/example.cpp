//
// Created by lucas on 12/06/19.
//

#include "touchless.hpp"

using namespace touchless;


int main(int argc, char **argv)
{
    auto gesture = new Gesture();
    gesture->name = "test gesture";
    gesture->precision = 10.0;

    auto keyframe = new GestureKeyframe();
    keyframe->hands = new Hands();
    keyframe->hands->leftHand = new Hand();
    keyframe->hands->rightHand = new Hand();

    gesture->addKeyframe(keyframe);
    gesture->addKeyframe(keyframe);
    gesture->addKeyframe(keyframe);

    std::cout << gesture->toJSON().dump(2) << std::endl;
}