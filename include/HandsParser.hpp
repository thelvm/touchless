//
// Created by lucas on 12/06/19.
//

#ifndef TOUCHLESS_API_HANDSPARSER_HPP
#define TOUCHLESS_API_HANDSPARSER_HPP

#include <functional>

#include "Hands.hpp"
#include "Gesture.hpp"
#include "Leap.h"

namespace touchless {
class HandsParser : private Leap::Listener {
 private:
  std::unique_ptr<Leap::Controller> controller_;

  void onFrame(const Leap::Controller &t_controller) override;
  void onConnect(const Leap::Controller &t_controller) override;
  void onDisconnect(const Leap::Controller &t_controller) override;

  std::optional<touchless::Hands> ParseFrame(const Leap::Frame &frame);

  using OnHandsCallbackT = std::function<void(Hands)>;
  using OnCanParseCallbackT = std::function<void()>;
  using OnCannotParseCallbackT  = std::function<void()>;
  OnHandsCallbackT on_hands_;
  OnCanParseCallbackT on_can_parse_hands_;
  OnCannotParseCallbackT on_cannot_parse_hands_;

 public:
  HandsParser();
  [[nodiscard]] bool CanParse() const;
  void Start();
  void Stop();
  std::optional<touchless::Hands> GetHands();
  void SetOnHands(OnHandsCallbackT on_hands);
  void SetOnCanParseHands(OnCanParseCallbackT on_can_parse_hands);
  void SetOnCannotParseHands(OnCannotParseCallbackT on_cannot_parse);
};
} // namespace touchless

#endif //TOUCHLESS_API_HANDSPARSER_HPP
