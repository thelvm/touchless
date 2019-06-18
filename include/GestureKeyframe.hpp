//
// Created by lucas on 12/06/19.
//

#ifndef GESTURE_PARSER_API_GESTUREKEYFRAME_HPP
#define GESTURE_PARSER_API_GESTUREKEYFRAME_HPP

#include "Hands.hpp"
#include "json.hpp"

namespace gesture_parser
{
class GestureKeyframe
{
public:
    Hands hands;

    GestureKeyframe();

    explicit GestureKeyframe(const nlohmann::json &t_json);

    static double positionPrecision;
};
} // namespace gesture_parser

#endif //GESTURE_PARSER_API_GESTUREKEYFRAME_HPP
