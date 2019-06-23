#ifndef TOUCHLESS_API_HANDS_PARSER_LISTENER
#define TOUCHLESS_API_HANDS_PARSER_LISTENER

#include "Hands.hpp"

namespace touchless
{
class HandsParserListener
{
public:
    virtual void onHands(const Hands *t_hands){};
    virtual void onConnect(){};
    virtual void onDisconnect(){};
};
} // namespace touchless

#endif