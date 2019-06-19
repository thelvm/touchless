//
// Created by lucas on 12/06/19.
//

#include "gesture_parser.hpp"

using namespace gesture_parser;

class myListener : public GestureParserListener
{
    void onConnect() override
    {
        printf("Connected!\n");
    }

    void onDisconnect() override
    {
        printf("Disconnected!\n");
    }

    void onGesture(char *t_gesture_name) override
    {
        printf("%s", t_gesture_name);
    }
};

int main(int argc, char **argv)
{
    auto gestureParser = new GestureParser();
    myListener *listener = new myListener();
    gestureParser->setListener(listener);
}