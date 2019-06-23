//
// Created by lucas on 12/06/19.
//

#include "HandsParser.hpp"

touchless::HandsParser::HandsParser()
{
    m_controller = new Leap::Controller;
    m_listener = nullptr;
}

bool touchless::HandsParser::canParse() const
{
    return m_controller->isConnected();
}

void touchless::HandsParser::onFrame(const Leap::Controller &t_controller)
{
    if (m_listener != nullptr)
    {
        Hands *hands = parseFrame(t_controller.frame());
        if (hands != nullptr)
        {
            m_listener->onHands(hands);
        }
    }
}

void touchless::HandsParser::onConnect(const Leap::Controller &t_controller)
{
    if (m_listener != nullptr)
    {
        m_listener->onConnect();
    }
}

void touchless::HandsParser::onDisconnect(const Leap::Controller &t_controller)
{
    if (m_listener != nullptr)
    {
        m_listener->onDisconnect();
    }
}

touchless::Hands *touchless::HandsParser::parseFrame(Leap::Frame t_frame)
{
    Hands *hands;

    if (!t_frame.hands().isEmpty())
    {
        hands = new Hands();
        for (int i = 0; i < t_frame.hands().count(); i++)
        {
            Leap::Hand hand = t_frame.hands()[i];

            // Identifying presence of hand
            if (hand.isLeft())
            {
                hands->leftHand = new Hand();
            }
            if (hand.isRight())
            {
                hands->rightHand = new Hand();
            }

            if (hand.isLeft())
            {
                hands->leftHand->setRollRadian(hand.palmNormal().roll());
            }
            else
            {
                hands->rightHand->setRollRadian(hand.palmNormal().roll());
            }

            if (hand.isLeft())
            {
                hands->leftHand->setPitchRadian(hand.direction().pitch());
            }
            else
            {
                hands->rightHand->setPitchRadian(hand.direction().pitch());
            }

            if (hand.isLeft())
            {
                hands->leftHand->setYawRadian(hand.direction().yaw());
            }
            else
            {
                hands->rightHand->setYawRadian(hand.direction().yaw());
            }

            for (int j = 0; j < hand.fingers().count(); j++)
            {
                Leap::Finger finger = hand.fingers()[j];

                switch (finger.type())
                {
                case Leap::Finger::TYPE_INDEX:
                    if (hand.isLeft())
                    {
                        hands->leftHand->setIndexExtended(finger.isExtended());
                    }
                    else
                    {
                        hands->rightHand->setIndexExtended(finger.isExtended());
                    }
                    break;
                case Leap::Finger::TYPE_MIDDLE:
                    if (hand.isLeft())
                    {
                        hands->leftHand->setMiddleExtended(finger.isExtended());
                    }
                    else
                    {
                        hands->rightHand->setMiddleExtended(finger.isExtended());
                    }
                    break;
                case Leap::Finger::TYPE_RING:
                    if (hand.isLeft())
                    {
                        hands->leftHand->setRingExtended(finger.isExtended());
                    }
                    else
                    {
                        hands->rightHand->setRingExtended(finger.isExtended());
                    }
                    break;
                case Leap::Finger::TYPE_PINKY:
                    if (hand.isLeft())
                    {
                        hands->leftHand->setPinkyExtended(finger.isExtended());
                    }
                    else
                    {
                        hands->rightHand->setPinkyExtended(finger.isExtended());
                    }
                    break;
                case Leap::Finger::TYPE_THUMB:
                    if (hand.isLeft())
                    {
                        hands->leftHand->setThumbExtended(finger.isExtended());
                    }
                    else
                    {
                        hands->rightHand->setThumbExtended(finger.isExtended());
                    }
                    break;
                default:
                    break;
                }
            }

            if (hand.isLeft())
            {
                hands->leftHand->position_x = hand.palmPosition().x;
                hands->leftHand->position_y = hand.palmPosition().y;
                hands->leftHand->position_z = hand.palmPosition().z;
            }
            else if (hand.isRight())
            {
                hands->rightHand->position_x = hand.palmPosition().x;
                hands->rightHand->position_y = hand.palmPosition().y;
                hands->rightHand->position_z = hand.palmPosition().z;
            }
        }
    }
    else
    {
        hands = nullptr;
    }

    return hands;
}

touchless::Hands *touchless::HandsParser::getHands()
{
    return parseFrame(m_controller->frame());
}

void touchless::HandsParser::start()
{
    m_controller->addListener(*this);
    if (m_listener != nullptr)
    {
        m_listener->onDisconnect();
    }
}

void touchless::HandsParser::stop()
{
    m_controller->removeListener(*this);
}

void touchless::HandsParser::setListener(touchless::HandsParserListener *t_listener)
{
    m_listener = t_listener;
}