#include "GestureParser.hpp"

touchless::GestureParser::GestureParser()
{
    m_listener = nullptr;
    m_handsParser = new HandsParser();
    m_handsParser->setListener(this);
}

void touchless::GestureParser::setListener(touchless::GestureParserListener *t_listener)
{
    m_listener = t_listener;
}

void touchless::GestureParser::start()
{
    m_handsParser->start();
}

void touchless::GestureParser::stop()
{
    m_handsParser->stop();
}

void touchless::GestureParser::addOrReplaceGesture(touchless::Gesture *t_gesture)
{
    m_gestures.insert_or_assign(t_gesture->name, t_gesture);
}

void touchless::GestureParser::removeGesture(char *t_gestureName)
{
    m_gestures.erase(t_gestureName);
}

void touchless::GestureParser::onConnect()
{
    if (m_listener != nullptr)
    {
        m_listener->onConnect();
    }
}

void touchless::GestureParser::onDisconnect()
{
    if (m_listener != nullptr)
    {
        m_listener->onDisconnect();
    }
}

void touchless::GestureParser::onHands(const touchless::Hands *t_hands)
{
    parseHands(t_hands);
}

void touchless::GestureParser::parseHands(const touchless::Hands *t_parsedHands)
{
}
