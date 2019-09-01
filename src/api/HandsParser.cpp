#include <utility>

#include "HandsParser.hpp"

touchless::HandsParser::HandsParser() {
  controller_ = std::make_unique<Leap::Controller>();
}

bool touchless::HandsParser::CanParse() const {
  return controller_->isConnected();
}

void touchless::HandsParser::onFrame(const Leap::Controller &t_controller) {
  if (on_hands_ != nullptr) {
    auto hands = ParseFrame(t_controller.frame());
    if (hands) {
      on_hands_(hands.value());
    }
  }
}

void touchless::HandsParser::onConnect(const Leap::Controller &t_controller) {
  if (on_can_parse_hands_ != nullptr) {
    on_can_parse_hands_();
  }
}

void touchless::HandsParser::onDisconnect(const Leap::Controller &t_controller) {
  if (on_cannot_parse_hands_ != nullptr) {
    on_cannot_parse_hands_();
  }
}

std::optional<touchless::Hands> touchless::HandsParser::ParseFrame(const Leap::Frame &frame) {
  if (!frame.hands().isEmpty()) {
    Hands hands;
    for (int i = 0; i < frame.hands().count(); i++) {
      Leap::Hand leap_hand = frame.hands()[i];

      // Identifying presence of hand
      if (leap_hand.isLeft()) {
        hands.left_hand_ = Hand();
      }
      if (leap_hand.isRight()) {
        hands.right_hand_ = Hand();
      }

      if (leap_hand.isLeft()) {
        hands.left_hand_->setRollRadian(leap_hand.palmNormal().roll());
      } else {
        hands.right_hand_->setRollRadian(leap_hand.palmNormal().roll());
      }

      if (leap_hand.isLeft()) {
        hands.left_hand_->setPitchRadian(leap_hand.direction().pitch());
      } else {
        hands.right_hand_->setPitchRadian(leap_hand.direction().pitch());
      }

      if (leap_hand.isLeft()) {
        hands.left_hand_->setYawRadian(leap_hand.direction().yaw());
      } else {
        hands.right_hand_->setYawRadian(leap_hand.direction().yaw());
      }

      for (int j = 0; j < leap_hand.fingers().count(); j++) {
        Leap::Finger finger = leap_hand.fingers()[j];

        switch (finger.type()) {
          case Leap::Finger::TYPE_INDEX:
            if (leap_hand.isLeft()) {
              hands.left_hand_->setIndexExtended(finger.isExtended());
            } else {
              hands.right_hand_->setIndexExtended(finger.isExtended());
            }
            break;
          case Leap::Finger::TYPE_MIDDLE:
            if (leap_hand.isLeft()) {
              hands.left_hand_->setMiddleExtended(finger.isExtended());
            } else {
              hands.right_hand_->setMiddleExtended(finger.isExtended());
            }
            break;
          case Leap::Finger::TYPE_RING:
            if (leap_hand.isLeft()) {
              hands.left_hand_->setRingExtended(finger.isExtended());
            } else {
              hands.right_hand_->setRingExtended(finger.isExtended());
            }
            break;
          case Leap::Finger::TYPE_PINKY:
            if (leap_hand.isLeft()) {
              hands.left_hand_->setPinkyExtended(finger.isExtended());
            } else {
              hands.right_hand_->setPinkyExtended(finger.isExtended());
            }
            break;
          case Leap::Finger::TYPE_THUMB:
            if (leap_hand.isLeft()) {
              hands.left_hand_->setThumbExtended(finger.isExtended());
            } else {
              hands.right_hand_->setThumbExtended(finger.isExtended());
            }
            break;
          default:break;
        }
      }

      if (leap_hand.isLeft()) {
        hands.left_hand_->position_x = leap_hand.palmPosition().x;
        hands.left_hand_->position_y = leap_hand.palmPosition().y;
        hands.left_hand_->position_z = leap_hand.palmPosition().z;
      } else if (leap_hand.isRight()) {
        hands.right_hand_->position_x = leap_hand.palmPosition().x;
        hands.right_hand_->position_y = leap_hand.palmPosition().y;
        hands.right_hand_->position_z = leap_hand.palmPosition().z;
      }
    }
    return hands;
  }
  return std::nullopt;
}

std::optional<touchless::Hands> touchless::HandsParser::GetHands() {
  return ParseFrame(controller_->frame());
}

void touchless::HandsParser::Start() {
  controller_->addListener(*this);
}

void touchless::HandsParser::Stop() {
  controller_->removeListener(*this);
}

void touchless::HandsParser::SetOnHands(OnHandsCallbackT on_hands) {
  on_hands_ = std::move(on_hands);
}

void touchless::HandsParser::SetOnCanParseHands(OnCanParseCallbackT on_can_parse_hands) {
  on_can_parse_hands_ = std::move(on_can_parse_hands);
}

void touchless::HandsParser::SetOnCannotParseHands(OnCannotParseCallbackT on_cannot_parse_hands) {
  on_cannot_parse_hands_ = std::move(on_cannot_parse_hands);
}