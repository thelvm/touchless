//
// Created by lucas on 12/06/19.
//

#include "HandsParser.hpp"

gesture_parser::HandsParser::HandsParser()
{
    m_controller = new Leap::Controller;
    m_listener = nullptr;
}

bool gesture_parser::HandsParser::canParse() const
{
    return m_controller->isConnected();
}

void gesture_parser::HandsParser::onFrame(const Leap::Controller &t_controller)
{
    if (m_listener != nullptr)
    {
        ParsedHands *parsedHands = parseFrame(t_controller.frame());
        if (parsedHands != nullptr)
        {
            m_listener->onHands(parsedHands);
        }
    }
}

void gesture_parser::HandsParser::onConnect(const Leap::Controller &t_controller)
{
    if (m_listener != nullptr)
    {
        m_listener->onConnect();
    }
}

void gesture_parser::HandsParser::onDisconnect(const Leap::Controller &t_controller)
{
    if (m_listener != nullptr)
    {
        m_listener->onDisconnect();
    }
}

gesture_parser::ParsedHands *gesture_parser::HandsParser::parseFrame(Leap::Frame t_frame)
{
    ParsedHands *parsedHands;

    if (!t_frame.hands().isEmpty())
    {
        parsedHands = new ParsedHands();
        for (int i = 0; i < t_frame.hands().count(); i++)
        {
            Leap::Hand hand = t_frame.hands()[i];

            // Identifying presence of hand
            if (hand.isLeft())
            {
                parsedHands->leftHand = new ParsedHand();
            }
            if (hand.isRight())
            {
                parsedHands->rightHand = new ParsedHand();
            }

            if (hand.isLeft())
            {
                parsedHands->leftHand->setRollRadian(hand.palmNormal().roll());
            }
            else
            {
                parsedHands->rightHand->setRollRadian(hand.palmNormal().roll());
            }

            if (hand.isLeft())
            {
                parsedHands->leftHand->setPitchRadian(hand.direction().pitch());
            }
            else
            {
                parsedHands->rightHand->setPitchRadian(hand.direction().pitch());
            }

            if (hand.isLeft())
            {
                parsedHands->leftHand->setYawRadian(hand.direction().yaw());
            }
            else
            {
                parsedHands->rightHand->setYawRadian(hand.direction().yaw());
            }

            for (int j = 0; j < hand.fingers().count(); j++)
            {
                Leap::Finger finger = hand.fingers()[j];

                switch (finger.type())
                {
                case Leap::Finger::TYPE_INDEX:
                    if (hand.isLeft())
                    {
                        parsedHands->leftHand->setIndexExtended(finger.isExtended());
                    }
                    else
                    {
                        parsedHands->rightHand->setIndexExtended(finger.isExtended());
                    }
                    break;
                case Leap::Finger::TYPE_MIDDLE:
                    if (hand.isLeft())
                    {
                        parsedHands->leftHand->setMiddleExtended(finger.isExtended());
                    }
                    else
                    {
                        parsedHands->rightHand->setMiddleExtended(finger.isExtended());
                    }
                    break;
                case Leap::Finger::TYPE_RING:
                    if (hand.isLeft())
                    {
                        parsedHands->leftHand->setRingExtended(finger.isExtended());
                    }
                    else
                    {
                        parsedHands->rightHand->setRingExtended(finger.isExtended());
                    }
                    break;
                case Leap::Finger::TYPE_PINKY:
                    if (hand.isLeft())
                    {
                        parsedHands->leftHand->setPinkyExtended(finger.isExtended());
                    }
                    else
                    {
                        parsedHands->rightHand->setPinkyExtended(finger.isExtended());
                    }
                    break;
                case Leap::Finger::TYPE_THUMB:
                    if (hand.isLeft())
                    {
                        parsedHands->leftHand->setThumbExtended(finger.isExtended());
                    }
                    else
                    {
                        parsedHands->rightHand->setThumbExtended(finger.isExtended());
                    }
                    break;
                default:
                    break;
                }
            }

            if (hand.isLeft())
            {
                parsedHands->leftHand->position_x = hand.palmPosition().x;
                parsedHands->leftHand->position_y = hand.palmPosition().y;
                parsedHands->leftHand->position_z = hand.palmPosition().z;
            }
            else if (hand.isRight())
            {
                parsedHands->rightHand->position_x = hand.palmPosition().x;
                parsedHands->rightHand->position_y = hand.palmPosition().y;
                parsedHands->rightHand->position_z = hand.palmPosition().z;
            }
        }
    }
    else
    {
        parsedHands = nullptr;
    }

    return parsedHands;
}

gesture_parser::ParsedHands *gesture_parser::HandsParser::getHands()
{
    return parseFrame(m_controller->frame());
}

void gesture_parser::HandsParser::startParsing()
{
    m_controller->addListener(*this);
    if (m_listener != nullptr)
    {
        m_listener->onDisconnect();
    }
}

void gesture_parser::HandsParser::stopParsing()
{
    m_controller->removeListener(*this);
}
