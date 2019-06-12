//
// Created by lucas on 12/06/19.
//

#ifndef GESTURE_PARSER_API_PARSEDHANDS_HPP
#define GESTURE_PARSER_API_PARSEDHANDS_HPP

#include "ParsedHand.hpp"

namespace gesture_parser {
    class ParsedHands {
    public:
        ParsedHand *leftHand;
        ParsedHand *rightHand;

        ParsedHands();
    };
}

#endif //GESTURE_PARSER_API_PARSEDHANDS_HPP
