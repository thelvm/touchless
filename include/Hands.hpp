#ifndef TOUCHLESS_API_HANDS_HPP
#define TOUCHLESS_API_HANDS_HPP

#include "json.hpp"
#include "Hand.hpp"

namespace touchless {
class Hands {
 public:
  std::optional<Hand> left_hand_;
  std::optional<Hand> right_hand_;

  bool Equals(Hands *other, double distance_tolerance) const;
  [[nodiscard]] double DistanceBetweenHandsX() const;
  [[nodiscard]] double DistanceBetweenHandsY() const;
  [[nodiscard]] double DistanceBetweenHandsZ() const;
  [[nodiscard]] double DistanceBetweenHands() const;
  [[nodiscard]] nlohmann::json ToJson();
  void FromJson(nlohmann::json j);
};
} // namespace touchless

#endif //TOUCHLESS_API_HandS_HPP
