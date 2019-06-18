//
// Created by lucas on 12/06/19.
//

#ifndef GESTURE_PARSER_API_HANDSPARSER_HPP
#define GESTURE_PARSER_API_HANDSPARSER_HPP

#include "Hands.hpp"
#include "Gesture.hpp"
#include "Leap.h"
#include "HandsParserListener.hpp"

namespace gesture_parser
{
class HandsParser : private Leap::Listener
{
private:
    Leap::Controller *m_controller;

    HandsParserListener *m_listener;

    void onFrame(const Leap::Controller &t_controller) override;

    void onConnect(const Leap::Controller &t_controller) override;

    void onDisconnect(const Leap::Controller &t_controller) override;

    Hands *parseFrame(Leap::Frame t_frame);

public:
    HandsParser();

    bool canParse() const;

    void start();

    void stop();

    Hands *getHands();

    void setListener(HandsParserListener *t_listener);
};
} // namespace gesture_parser

#endif //GESTURE_PARSER_API_HANDSPARSER_HPP
