//
// Created by lucas on 23/06/19.
//

#include <touchless.hpp>

bool touchless::isLeapDaemonRunning()
{
    int isActiveReturnCode = system("systemctl is-active --quiet leapd");
    return isActiveReturnCode == 0;
}
