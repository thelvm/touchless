//
// Created by lucas on 12/06/19.
//

#include "touchless.hpp"

using namespace touchless;

class myListener : public GestureParserListener
{
    void onCanParseGesture() override
    {
        printf("Connected!\n");
    }

    void onCannotParseGesture() override
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
    if (!isLeapDaemonRunning())
    {
        startLeapDaemon();
    }
    auto gestureParser = new GestureParser();
    auto *listener = new myListener();
    gestureParser->setListener(listener);
}