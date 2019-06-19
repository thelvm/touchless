#include "GestureParser.hpp"

gesture_parser::GestureParser::GestureParser()
{
    m_listener = nullptr;
    m_handsParser = new HandsParser();
    m_handsParser->setListener(this);
}

void gesture_parser::GestureParser::setListener(gesture_parser::GestureParserListener *t_listener)
{
    m_listener = t_listener;
}

void gesture_parser::GestureParser::start()
{
    m_handsParser->start();
}

void gesture_parser::GestureParser::stop()
{
    m_handsParser->stop();
}

void gesture_parser::GestureParser::addOrReplaceGesture(gesture_parser::Gesture *t_gesture)
{
    m_gestures.insert_or_assign(t_gesture->name, t_gesture);
}

void gesture_parser::GestureParser::removeGesture(char *t_gestureName)
{
    m_gestures.erase(t_gestureName);
}

void gesture_parser::GestureParser::onConnect()
{
    if (m_listener != nullptr)
    {
        m_listener->onConnect();
    }
}

void gesture_parser::GestureParser::onDisconnect()
{
    if (m_listener != nullptr)
    {
        m_listener->onDisconnect();
    }
}

void gesture_parser::GestureParser::onHands(const gesture_parser::Hands *t_hands)
{
    parseHands(t_hands);
}

void gesture_parser::GestureParser::parseHands(const gesture_parser::Hands *t_parsedHands)
{
}
