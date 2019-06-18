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

void onHands(gesture_parser::ParsedHands *t_gesture)
{
}

int main(int argc, char **argv)
{
    auto pHandsParser = new gesture_parser::HandsParser();

    pHandsParser->setOnConnectCallback(onConnect);
    pHandsParser->setOnDisconnectCallback(onDisconnect);
    pHandsParser->setOnGestureCallback(onHands);

    pHandsParser->startParsing();

    std::cin.get();

    pHandsParser->stopParsing();
}