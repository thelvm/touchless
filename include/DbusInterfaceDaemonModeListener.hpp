//
// Created by lucas on 23/06/19.
//

#ifndef TOUCHLESS_API_DBUSINTERFACEDAEMONMODELISTENER_HPP
#define TOUCHLESS_API_DBUSINTERFACEDAEMONMODELISTENER_HPP

namespace touchless
{
    class DbusInterfaceDaemonModeListener
    {
    public:
        virtual void onBusConnect()
        {};

        virtual void onNameOwned()
        {};

        virtual void onNameLost()
        {};
    };
}
#endif //TOUCHLESS_API_DBUSINTERFACEDAEMONMODELISTENER_HPP
