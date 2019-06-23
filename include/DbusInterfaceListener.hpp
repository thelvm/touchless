//
// Created by lucas on 23/06/19.
//

#ifndef TOUCHLESS_API_DBUSINTERFACELISTENER_HPP
#define TOUCHLESS_API_DBUSINTERFACELISTENER_HPP

namespace touchless
{
    class DbusInterfaceListener
    {
    public:
        virtual void onGestureSignal(const char *t_gestureName)
        {};
    };
}

#endif //TOUCHLESS_API_DBUSINTERFACELISTENER_HPP
