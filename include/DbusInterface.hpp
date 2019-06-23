//
// Created by lucas on 23/06/19.
//

#ifndef TOUCHLESS_API_DBUSINTERFACE_HPP
#define TOUCHLESS_API_DBUSINTERFACE_HPP

#include "touchless_gdbus_proxy.h"
#include "touchless_gdbus_common.h"
#include "DbusInterfaceListener.hpp"
#include "DbusInterfaceDaemonModeListener.hpp"

namespace touchless
{
    class DbusInterface
    {
    private:
        static Glib::RefPtr<touchless::daemonProxy> m_daemonProxy;
        static DbusInterfaceListener *m_listener;
        static DbusInterfaceDaemonModeListener *m_daemonModeListener;

        guint m_dbusNameIdentifier;
        const char *M_BUS_NAME = "com.thelvm.touchless";
        const char *M_OBJECT_PATH = "com/thelvm/touchless/daemon";

        void genericStart();

        static void onGestureDetected(const Glib::ustring &t_gestureName);

        static void onBusConnect(const Glib::RefPtr<Gio::DBus::Connection> &t_connection, const Glib::ustring& t_name);

        static void onNameOwned(const Glib::RefPtr<Gio::DBus::Connection> &t_connection, const Glib::ustring& t_name);

        static void onNameLost(const Glib::RefPtr<Gio::DBus::Connection> &t_connection, const Glib::ustring& t_name);

    public:
        void startInDaemonMode();

        void startInListenerMode();

        void emitGestureDetected(const char *t_gestureName);

        void setListener(DbusInterfaceListener *t_listener);

        void setDaemonModeListener(DbusInterfaceDaemonModeListener *t_daemonModeListener);
    };
}

#endif //TOUCHLESS_API_DBUSINTERFACE_HPP
