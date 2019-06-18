#include "GestureParser.hpp"

gesture_parser::GestureParser::GestureParser()
{
    m_listener = nullptr;
    m_handsParser = new HandsParser();
    m_handsParser->addListener(this);
}

void gesture_parser::GestureParser::addListener(gesture_parser::GestureParserListener *t_listener)
{
    m_listener = t_listener;
}

void gesture_parser::GestureParser::start()
{
}

void gesture_parser::GestureParser::stop()
{
}

void gesture_parser::GestureParser::removeGesture(const char *t_gestureName)
{
}

void gesture_parser::GestureParser::onConnect()
{
}

void gesture_parser::GestureParser::onDisconnect()
{
}

void gesture_parser::GestureParser::onHands(const gesture_parser::ParsedHands *t_hands)
{
}
