#include "GestureParser.hpp"
#include <filesystem>

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

void touchless::GestureParser::onCanParseHands()
{
    if (m_listener != nullptr)
    {
        m_listener->onCanParseGesture();
    }
}

void touchless::GestureParser::onCannotParseHands()
{
    if (m_listener != nullptr)
    {
        m_listener->onCannotParseGesture();
    }
}

void touchless::GestureParser::onHands(const touchless::Hands *t_hands)
{
    parseHands(t_hands);
}

void touchless::GestureParser::parseHands(const touchless::Hands *t_parsedHands)
{
}

void touchless::GestureParser::loadGesturesFromDir(std::string t_dirPath)
{
    m_gestures.clear();
    for (auto & entry : std::filesystem::directory_iterator(t_dirPath))
    {
        if (entry.is_regular_file())
        {
            auto gesture = new Gesture();
            gesture->fromFile(entry.path());
            addOrReplaceGesture(gesture);
        }
    }
}
