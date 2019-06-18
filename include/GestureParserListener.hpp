#ifndef GESTURE_PARSER_API_GESTURE_PARSER_LISTENER
#define GESTURE_PARSER_API_GESTURE_PARSER_LISTENER

#include "Gesture.hpp"

namespace gesture_parser
{
class GestureParserListener
{
public:
    virtual void onGesture(const Gesture *&t_gesture);

    virtual void onConnect();

    virtual void onDisconnect();
};
} // namespace gesture_parser

#endif