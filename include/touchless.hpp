//
// Created by lucas on 12/06/19.
//

#ifndef TOUCHLESS_API_GESTURE_PARSER_HPP
#define TOUCHLESS_API_GESTURE_PARSER_HPP

#include "Hand.hpp"
#include "Hands.hpp"
#include "HandsParserListener.hpp"
#include "HandsParser.hpp"
#include "GestureParserListener.hpp"
#include "GestureParser.hpp"
#include "DbusInterfaceListener.hpp"
#include "DbusInterfaceDaemonModeListener.hpp"
#include "DbusInterface.hpp"

namespace touchless
{
    bool isLeapDaemonRunning();
    void startLeapDaemon();
    void stopLeapDaemon();
}

#endif //TOUCHLESS_API_GESTURE_PARSER_HPP
