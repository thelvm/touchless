//
// Created by lucas on 12/06/19.
//

#include "HandsParser.hpp"

gesture_parser::HandsParser::HandsParser() {
    m_controller = new Leap::Controller;

    m_onGestureCallback = nullptr;
    m_onConnectCallback = nullptr;
    m_onDisconnectCallback = nullptr;
}

bool gesture_parser::HandsParser::canParseHands() {
    return false;
}

void gesture_parser::HandsParser::onFrame(const Leap::Controller &t_controller) {
    if (m_onGestureCallback != nullptr) {
        ParsedHands *parsedHands = parseFrame(t_controller.frame());
        if (parsedHands != nullptr) {
            m_onGestureCallback(parsedHands);
        }
    }
}

void gesture_parser::HandsParser::onConnect(const Leap::Controller &t_controller) {
    if (m_onConnectCallback != nullptr) {
        m_onConnectCallback();
    }
}

void gesture_parser::HandsParser::onDisconnect(const Leap::Controller &t_controller) {
    if (m_onDisconnectCallback != nullptr) {
        m_onDisconnectCallback();
    }
}

gesture_parser::ParsedHands *gesture_parser::HandsParser::parseFrame(Leap::Frame t_frame) {
    ParsedHands *parsedHands;

    if (!t_frame.hands().isEmpty()) {
        parsedHands = new ParsedHands();
        for (int i = 0; i < t_frame.hands().count(); i++) {
            Leap::Hand hand = t_frame.hands()[i];

            // Identifying presence of hand
            if (hand.isLeft()) {
                parsedHands->leftHand = new ParsedHand();
            }
            if (hand.isRight()) {
                parsedHands->rightHand = new ParsedHand();
            }

            if (hand.isLeft()) {
                parsedHands->leftHand->setRollRadian(hand.palmNormal().roll());
            } else {
                parsedHands->rightHand->setRollRadian(hand.palmNormal().roll());
            }


            if (hand.isLeft()) {
                parsedHands->leftHand->setPitchRadian(hand.direction().pitch());
            } else {
                parsedHands->rightHand->setPitchRadian(hand.direction().pitch());
            }

            if (hand.isLeft()) {
                parsedHands->leftHand->setYawRadian(hand.direction().yaw());
            } else {
                parsedHands->rightHand->setYawRadian(hand.direction().yaw());
            }

            for (int j = 0; j < hand.fingers().count(); j++) {
                Leap::Finger finger = hand.fingers()[j];

                switch (finger.type()) {
                    case Leap::Finger::TYPE_INDEX:
                        if (hand.isLeft()) {
                            parsedHands->leftHand->setIndexExtended(finger.isExtended());
                        } else {
                            parsedHands->rightHand->setIndexExtended(finger.isExtended());
                        }
                        break;
                    case Leap::Finger::TYPE_MIDDLE:
                        if (hand.isLeft()) {
                            parsedHands->leftHand->setMiddleExtended(finger.isExtended());
                        } else {
                            parsedHands->rightHand->setMiddleExtended(finger.isExtended());
                        }
                        break;
                    case Leap::Finger::TYPE_RING:
                        if (hand.isLeft()) {
                            parsedHands->leftHand->setRingExtended(finger.isExtended());
                        } else {
                            parsedHands->rightHand->setRingExtended(finger.isExtended());
                        }
                        break;
                    case Leap::Finger::TYPE_PINKY:
                        if (hand.isLeft()) {
                            parsedHands->leftHand->setPinkyExtended(finger.isExtended());
                        } else {
                            parsedHands->rightHand->setPinkyExtended(finger.isExtended());
                        }
                        break;
                    case Leap::Finger::TYPE_THUMB:
                        if (hand.isLeft()) {
                            parsedHands->leftHand->setThumbExtended(finger.isExtended());
                        } else {
                            parsedHands->rightHand->setThumbExtended(finger.isExtended());
                        }
                        break;
                    default:
                        break;
                }
            }

            if (hand.isLeft()) {
                parsedHands->leftHand->position_x = (int) (hand.palmPosition().x - hand.palmPosition().x);
                parsedHands->leftHand->position_y = (int) (hand.palmPosition().y - hand.palmPosition().y);
                parsedHands->leftHand->position_z = (int) (hand.palmPosition().z - hand.palmPosition().z);
            } else if (hand.isRight()) {
                parsedHands->rightHand->position_x = (int) (hand.palmPosition().x - hand.palmPosition().x);
                parsedHands->rightHand->position_y = (int) (hand.palmPosition().y - hand.palmPosition().y);
                parsedHands->rightHand->position_z = (int) (hand.palmPosition().z - hand.palmPosition().z);
            }
        }
    } else {
        parsedHands = nullptr;
    }

    return parsedHands;
}

void gesture_parser::HandsParser::setOnGestureCallback(void (*t_onGestureCallback)(ParsedHands *)) {
    m_onGestureCallback = t_onGestureCallback;
}

void gesture_parser::HandsParser::removeOnGestureCallback() {
    m_onGestureCallback = nullptr;
}

void gesture_parser::HandsParser::setOnConnectCallback(void (*t_onConnectCallback)()) {
    m_onConnectCallback = t_onConnectCallback;
}

void gesture_parser::HandsParser::removeOnConnectCallback() {
    m_onConnectCallback = nullptr;
}

void gesture_parser::HandsParser::setOnDisconnectCallback(void (*t_onDisconnectCallback)()) {
    m_onDisconnectCallback = t_onDisconnectCallback;
}

void gesture_parser::HandsParser::removeOnDisconnectCallback() {
    m_onDisconnectCallback = nullptr;
}

gesture_parser::ParsedHands *gesture_parser::HandsParser::getParsedHands() {
    return parseFrame(m_controller->frame());
}

void gesture_parser::HandsParser::startParsing() {
    m_controller->addListener(*this);
}

void gesture_parser::HandsParser::stopParsing() {
    m_controller->removeListener(*this);
}

