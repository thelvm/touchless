#ifndef GESTURE_PARSER_API_HANDS_PARSER_LISTENER
#define GESTURE_PARSER_API_HANDS_PARSER_LISTENER

#include "ParsedHands.hpp"

namespace gesture_parser
{
class HandsParserListener
{
public:
    virtual void onHands(const ParsedHands *t_hands);
    virtual void onConnect();
    virtual void onDisconnect();
};
} // namespace gesture_parser

#endif