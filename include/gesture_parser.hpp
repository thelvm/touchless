//
// Created by lucas on 12/06/19.
//

#ifndef GESTURE_PARSER_API_GESTURE_PARSER_HPP
#define GESTURE_PARSER_API_GESTURE_PARSER_HPP

#include "Hand.hpp"
#include "Hands.hpp"
#include "HandsParserListener.hpp"
#include "HandsParser.hpp"
#include "GestureParserListener.hpp"
#include "GestureParser.hpp"

namespace gesture_parser
{
    bool isLeapDaemonRunning();
    void startLeapDaemon();
    void stopLeapDaemon();
}

#endif //GESTURE_PARSER_API_GESTURE_PARSER_HPP
