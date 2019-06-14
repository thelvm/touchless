//
// Created by lucas on 12/06/19.
//

#ifndef GESTURE_PARSER_API_GESTUREKEYFRAME_HPP
#define GESTURE_PARSER_API_GESTUREKEYFRAME_HPP

#include "ParsedHands.hpp"

namespace gesture_parser {
    class GestureKeyframe {
    public:
        ParsedHands hands;

        static double positionPrecision;
    };
}

#endif //GESTURE_PARSER_API_GESTUREKEYFRAME_HPP
