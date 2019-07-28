#include <cmath>

#include "Hands.hpp"

double touchless::Hands::DistanceBetweenHandsX() const {
  if (left_hand_ && right_hand_) {
    return fabs(left_hand_->position_x - right_hand_->position_x);
  }
  return -1;
}

double touchless::Hands::DistanceBetweenHandsY() const {
  if (left_hand_ && right_hand_) {
    return fabs(left_hand_->position_y - right_hand_->position_y);
  }
  return -1;
}

double touchless::Hands::DistanceBetweenHandsZ() const {
  if (left_hand_ && right_hand_) {
    return fabs(left_hand_->position_z - left_hand_->position_z);
  }
  return -1;
}

double touchless::Hands::DistanceBetweenHands() const {
  if (left_hand_ && right_hand_) {
    return sqrt(pow((left_hand_->position_x - right_hand_->position_x), 2) +
        pow((left_hand_->position_y - right_hand_->position_y), 2) +
        pow((left_hand_->position_z - right_hand_->position_z), 2));
  }
  return -1;
}

bool touchless::Hands::Equals(const Hands &other, double distance_tolerance) const {
  distance_tolerance /= 2;
  return left_hand_ == other.left_hand_ &&
      right_hand_ == other.right_hand_ &&

      (other.DistanceBetweenHandsX() - distance_tolerance) < DistanceBetweenHandsX() &&
      (other.DistanceBetweenHandsX() + distance_tolerance) > DistanceBetweenHandsX() &&

      (other.DistanceBetweenHandsY() - distance_tolerance) < DistanceBetweenHandsY() &&
      (other.DistanceBetweenHandsY() + distance_tolerance) > DistanceBetweenHandsY() &&

      (other.DistanceBetweenHandsZ() - distance_tolerance) < DistanceBetweenHandsZ() &&
      (other.DistanceBetweenHandsZ() + distance_tolerance) > DistanceBetweenHandsZ();
}

nlohmann::json touchless::Hands::ToJson() {
  nlohmann::json j;
  if (left_hand_) {
    j["left"] = left_hand_->toJSON();
  }
  if (right_hand_) {
    j["right"] = right_hand_->toJSON();
  }
  return j;
}

void touchless::Hands::FromJson(nlohmann::json j) {
  if (j.find("left") != j.end()) {
    if (!left_hand_) {
      left_hand_ = std::make_optional<Hand>();
    }
    left_hand_->fromJSON(j["left"]);
  } else {
    left_hand_.reset();
  }

  if (j.find("right") != j.end()) {
    if (!right_hand_) {
      right_hand_ = std::make_optional<Hand>();
    }
    right_hand_->fromJSON(j["right"]);
  } else {
    right_hand_.reset();
  }
}
