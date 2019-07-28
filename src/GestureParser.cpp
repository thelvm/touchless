#include "GestureParser.hpp"
#include <filesystem>

touchless::GestureParser::GestureParser() {
  hands_parser_ = std::make_unique<HandsParser>();

  hands_parser_->SetOnHands([this](const Hands &hands) {
    OnHands(hands);
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

void touchless::GestureParser::AddOrReplaceGesture(touchless::Gesture *t_gesture) {
  gestures_list_.insert_or_assign(t_gesture->name_, t_gesture);
}

void touchless::GestureParser::RemoveGesture(char *gesture_name) {
  gestures_list_.erase(gesture_name);
}

void touchless::GestureParser::OnCanParseHands() {
  if (m_listener != nullptr) {
    m_listener->onCanParseGesture();
  }
}

void touchless::GestureParser::OnCannotParseHands() {
  if (m_listener != nullptr) {
    m_listener->onCannotParseGesture();
  }
}

void touchless::GestureParser::OnHands(const Hands &t_hands) {
  ParseHands(t_hands);
}

void touchless::GestureParser::ParseHands(const Hands &parsed_hands) {
}

void touchless::GestureParser::LoadGesturesFromDir(const std::string& dir_path) {
  gestures_list_.clear();
  for (auto &entry : std::filesystem::directory_iterator(dir_path)) {
    if (entry.is_regular_file()) {
      auto gesture = new Gesture();
      gesture->FromFile(entry.path());
      AddOrReplaceGesture(gesture);
    }
  }
}
