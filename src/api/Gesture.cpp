//
// Created by lucas on 14/06/19.
//
#include <fstream>
#include <json.hpp>
#include <iostream>
#include "Gesture.hpp"

touchless::Gesture::Gesture() : current_keyframe_number_{0}, precision_{0} {
  last_keyframe_timestamp_ = clock();
};

void touchless::Gesture::AddKeyframe(const GestureKeyframe &t_keyframe) {
  keyframes_.push_back(t_keyframe);
}

void touchless::Gesture::AddKeyframe(const GestureKeyframe &t_keyframe, unsigned int t_position) {
  if (t_position < keyframes_.size()) {
    auto it = keyframes_.begin();
    keyframes_.insert(it + t_position, t_keyframe);
  }
}

void touchless::Gesture::RemoveKeyframe() {
  keyframes_.pop_back();
}

void touchless::Gesture::RemoveKeyframe(unsigned int t_position) {
  if (t_position < keyframes_.size()) {
    auto it = keyframes_.begin();
    keyframes_.erase(it + t_position);
  }
}

std::optional<touchless::GestureKeyframe> touchless::Gesture::GetKeyframe(unsigned int t_position) {
  if (t_position < keyframes_.size()) {
    return keyframes_[t_position];
  }
  return std::nullopt;
}

bool touchless::Gesture::TryHands(const Hands &t_hands) {
  clock_t time_since_last_keyframe = (clock() - last_keyframe_timestamp_) / CLOCKS_PER_SEC;
  if (current_keyframe_number_ != 0 ||
      (time_since_last_keyframe <= (keyframes_[current_keyframe_number_].max_delay_) &&
          time_since_last_keyframe >= (keyframes_[current_keyframe_number_].min_delay_))) {
    if (keyframes_[current_keyframe_number_].Compare(t_hands, precision_)) {
      double left_delta_x =
          fabs(keyframes_[current_keyframe_number_].hands_.left_hand_->position_x - t_hands.left_hand_->position_x);
      double left_delta_y =
          fabs(keyframes_[current_keyframe_number_].hands_.left_hand_->position_y - t_hands.left_hand_->position_z);
      double left_delta_z =
          fabs(keyframes_[current_keyframe_number_].hands_.left_hand_->position_z - t_hands.left_hand_->position_z);
      double right_delta_x = fabs(
          keyframes_[current_keyframe_number_].hands_.right_hand_->position_x - t_hands.right_hand_->position_x);
      double right_delta_y = fabs(
          keyframes_[current_keyframe_number_].hands_.right_hand_->position_y - t_hands.right_hand_->position_z);
      double right_delta_z = fabs(
          keyframes_[current_keyframe_number_].hands_.right_hand_->position_z - t_hands.right_hand_->position_z);

      if ((keyframes_[current_keyframe_number_].left_delta_x_ - precision_) < left_delta_x &&
          (keyframes_[current_keyframe_number_].left_delta_x_ + precision_) > left_delta_x &&

          (keyframes_[current_keyframe_number_].left_delta_y_ - precision_) < left_delta_y &&
          (keyframes_[current_keyframe_number_].left_delta_y_ + precision_) > left_delta_y &&

          (keyframes_[current_keyframe_number_].left_delta_z_ - precision_) < left_delta_z &&
          (keyframes_[current_keyframe_number_].left_delta_z_ + precision_) > left_delta_z &&

          (keyframes_[current_keyframe_number_].right_delta_x_ - precision_) < right_delta_x &&
          (keyframes_[current_keyframe_number_].right_delta_x_ + precision_) > right_delta_x &&

          (keyframes_[current_keyframe_number_].right_delta_y_ - precision_) < right_delta_y &&
          (keyframes_[current_keyframe_number_].right_delta_y_ + precision_) > right_delta_y &&

          (keyframes_[current_keyframe_number_].right_delta_z_ - precision_) < right_delta_z &&
          (keyframes_[current_keyframe_number_].right_delta_z_ + precision_) > right_delta_z) {
        current_keyframe_number_++;
        if (current_keyframe_number_ == keyframes_.size()) {
          current_keyframe_number_ = 0;
          return true;
        }
        last_keyframe_timestamp_ = clock();
        return false;
      }
    }
  }
  current_keyframe_number_ = 0;
  return false;
}

nlohmann::json touchless::Gesture::ToJson() {
  nlohmann::json j;

  j["name"] = name_;
  j["precision"] = precision_;
  j["keyframes"] = nlohmann::json::array();
  for (size_t i = 0; i < keyframes_.size(); i++) {
    j["keyframes"][i] = keyframes_[i].ToJson();
  }

  return j;
}

void touchless::Gesture::FromJson(nlohmann::json j) {
  name_ = j["name"];
  precision_ = j["precision"];

  keyframes_.clear();
  for (auto &json_keyframe : j["keyframes"]) {
    GestureKeyframe keyframe;
    keyframe.FromJson(json_keyframe);
    keyframes_.push_back(keyframe);
  }
}

void touchless::Gesture::FromFile(const std::string &json_file_name) {
  std::ifstream file_stream(json_file_name.c_str());
  if (file_stream.fail()) {
    std::cerr << "Error: " << strerror(errno);
    return;
  }
  nlohmann::json json_gesture;
  file_stream >> json_gesture;

  if (!json_gesture.empty()) {
    FromJson(json_gesture);
  } else {
    std::cout << json_file_name << " cannot be loaded. JSON is empty.\n";
  }
}