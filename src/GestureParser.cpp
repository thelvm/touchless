#include "GestureParser.hpp"
#include <filesystem>

touchless::GestureParser::GestureParser() {
  hands_parser_ = std::make_unique<HandsParser>();

  hands_parser_->SetOnHands([this](const Hands &hands) {
    AnalyseHands(hands);
  });
  hands_parser_->SetOnCanParseHands([this]() {
    OnCanParseHands();
  });
  hands_parser_->SetOnCannotParseHands([this]() {
    OnCannotParseHands();
  });
}

void touchless::GestureParser::Start() {
  hands_parser_->Start();
}

void touchless::GestureParser::Stop() {
  hands_parser_->Stop();
}

void touchless::GestureParser::AddOrReplaceGesture(const Gesture &t_gesture) {
  gestures_list_.insert_or_assign(t_gesture.name_, t_gesture);
}

void touchless::GestureParser::RemoveGesture(const std::string &gesture_name) {
  gestures_list_.erase(gesture_name);
}

void touchless::GestureParser::OnCanParseHands() {
}

void touchless::GestureParser::OnCannotParseHands() {
}

void touchless::GestureParser::AnalyseHands(const Hands &hands) {
  for(auto& gesture : gestures_list_) {
    if(gesture.second.TryHands(hands)) {
      // TODO call callback
    }
  }
}

void touchless::GestureParser::LoadGesturesFromDir(const std::string& dir_path) {
  gestures_list_.clear();
  for (auto &entry : std::filesystem::directory_iterator(dir_path)) {
    if (entry.is_regular_file()) {
      Gesture gesture;
      gesture.FromFile(entry.path());
      AddOrReplaceGesture(gesture);
    }
  }
}
