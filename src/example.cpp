//
// Created by lucas on 12/06/19.
//

#include "gesture_parser.hpp"

void onConnect() {
    printf("Connected!\n");
}

void onDisconnect() {
    printf("Disconnected!\n");
}

void onGesture(gesture_parser::ParsedHands *t_parsedHands) {
    if (t_parsedHands->getDistance() > 0) {
        printf("%f\n", t_parsedHands->getDistance());
    }
}

int main(int argc, char **argv) {
    auto pHandParser = new gesture_parser::HandsParser();

    pHandParser->setOnConnectCallback(onConnect);
    pHandParser->setOnDisconnectCallback(onDisconnect);
    pHandParser->setOnGestureCallback(onGesture);

    pHandParser->startParsing();

    std::cin.get();

    pHandParser->stopParsing();
}