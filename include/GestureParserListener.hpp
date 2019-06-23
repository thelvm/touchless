#ifndef TOUCHLESS_API_GESTURE_PARSER_LISTENER
#define TOUCHLESS_API_GESTURE_PARSER_LISTENER

#include "Gesture.hpp"

namespace touchless
{
class GestureParserListener
{
public:
    virtual void onGesture(char *t_gesture_name){};

    virtual void onConnect(){};

    virtual void onDisconnect(){};
};
} // namespace touchless

#endif