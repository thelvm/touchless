//
// Created by lucas on 12/06/19.
//

#ifndef GESTURE_PARSER_API_HANDSPARSER_HPP
#define GESTURE_PARSER_API_HANDSPARSER_HPP

#include "ParsedHands.hpp"
#include "Gesture.hpp"
#include "Leap.h"

namespace gesture_parser
{
class HandsParser : private Leap::Listener
{
private:
    Leap::Controller *m_controller;

    std::map<char *, Gesture> m_gestures;

    void (*m_onGestureCallback)(Gesture *);

    void (*m_onConnectCallback)();

    void (*m_onDisconnectCallback)();

    void onFrame(const Leap::Controller &t_controller) override;

    void onConnect(const Leap::Controller &t_controller) override;

    void onDisconnect(const Leap::Controller &t_controller) override;

    ParsedHands *parseFrame(Leap::Frame t_frame);

public:
    HandsParser();

    bool canParseHands();

    void startParsing();

    void stopParsing();

    ParsedHands *getParsedHands();

    void setOnGestureCallback(void (*t_onGestureCallback)(Gesture *));

    void removeOnGestureCallback();

    void setOnConnectCallback(void (*t_onConnectCallback)());

    void removeOnConnectCallback();

    void setOnDisconnectCallback(void (*t_onDisconnectCallback)());

    void removeOnDisconnectCallback();

    /// Adds or replaces a gesture to the list of gestures to detect
    void addGesture(Gesture *t_gesture);

    /// Removes a gesture by name from the list of gestures to detect
    void removeGesture(char *t_gestureName);

    /// Removes a gesture with same name from the list of gestures to detect
    void removeGesture(Gesture *t_gesture);
};
} // namespace gesture_parser

#endif //GESTURE_PARSER_API_HANDSPARSER_HPP
