//
// Created by lucas on 12/06/19.
//

#ifndef TOUCHLESS_API_HANDSPARSER_HPP
#define TOUCHLESS_API_HANDSPARSER_HPP

#include "Hands.hpp"
#include "Gesture.hpp"
#include "Leap.h"
#include "HandsParserListener.hpp"

namespace touchless
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
} // namespace touchless

#endif //TOUCHLESS_API_HANDSPARSER_HPP
