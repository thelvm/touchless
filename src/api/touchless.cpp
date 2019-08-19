//
// Created by lucas on 23/06/19.
//

#include <touchless.hpp>

bool touchless::IsLeapDaemonRunning()
{
    int is_active_return_code = system("systemctl is-active --quiet leapd");
    return is_active_return_code == 0;
}
