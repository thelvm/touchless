//
// Created by lucas on 23/06/19.
//

#include <gesture_parser.hpp>

bool gesture_parser::isLeapDaemonRunning()
{
    int isActiveReturnCode = system("systemctl is-active --quiet leapd");
    return isActiveReturnCode == 0;
}

