//
// Created by lucas on 12/06/19.
//

#include "gesture_parser.hpp"

void onConnect()
{
    printf("Connected!\n");
}

void onDisconnect()
{
    printf("Disconnected!\n");
}

void onGesture(gesture_parser::Gesture *t_gesture)
{
}

int main(int argc, char **argv)
{
    auto pHandsParser = new gesture_parser::HandsParser();

    pHandsParser->setOnConnectCallback(onConnect);
    pHandsParser->setOnDisconnectCallback(onDisconnect);
    pHandsParser->setOnGestureCallback(onGesture);

    pHandsParser->startParsing();

    std::cin.get();

    pHandsParser->stopParsing();
}