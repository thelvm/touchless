//
// Created by lucas on 12/06/19.
//

#ifndef TOUCHLESS_API_GESTUREKEYFRAME_HPP
#define TOUCHLESS_API_GESTUREKEYFRAME_HPP

#include <time.h>
#include "Hands.hpp"
#include "json.hpp"

namespace touchless
{
class GestureKeyframe
{
public:
    Hands *hands;

    static double positionPrecision;

    /// Maximum delay in seconds since the previous keyframe
    unsigned int maxDelay;

    /// Minimum delay in seconds since the previous keyframe
    unsigned int minDelay;

    double leftDeltaX;
    double leftDeltaY;
    double leftDeltaZ;

    double rightDeltaX;
    double rightDeltaY;
    double rightDeltaZ;

    GestureKeyframe();

    explicit GestureKeyframe(const nlohmann::json &t_json);

    bool compare(Hands *t_hands, double t_precision);
};
} // namespace touchless

#endif //TOUCHLESS_API_GESTUREKEYFRAME_HPP
