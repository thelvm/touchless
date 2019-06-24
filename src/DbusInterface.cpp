//
// Created by lucas on 23/06/19.
//

#include <giomm.h>
#include "touchless_gdbus_proxy.h"
#include "DbusInterface.hpp"

Glib::RefPtr<touchless::daemonProxy> touchless::DbusInterface::m_daemonProxy;
touchless::DbusInterfaceListener *touchless::DbusInterface::m_listener;
touchless::DbusInterfaceDaemonModeListener *touchless::DbusInterface::m_daemonModeListener;

void touchless::DbusInterface::genericStart()
{
    m_daemonProxy = touchless::daemonProxy::createForBus_sync(Gio::DBus::BUS_TYPE_SESSION,
                                                              Gio::DBus::PROXY_FLAGS_NONE,
                                                              M_BUS_NAME,
                                                              M_OBJECT_PATH);
}

void touchless::DbusInterface::onGestureDetected(const Glib::ustring &t_gestureName)
{
    if (m_listener != nullptr)
    {
        m_listener->onGestureSignal(t_gestureName.c_str());
    }
}

void touchless::DbusInterface::startInDaemonMode()
{
    genericStart();
    m_dbusNameIdentifier = Gio::DBus::own_name(Gio::DBus::BUS_TYPE_SESSION,
                                               M_BUS_NAME,
                                               sigc::ptr_fun(onBusConnect),
                                               sigc::ptr_fun(onNameOwned),
                                               sigc::ptr_fun(onNameLost));
}

void touchless::DbusInterface::startInListenerMode()
{
    genericStart();
    m_daemonProxy->gesture_detected_signal.connect(sigc::ptr_fun(onGestureDetected));
}

void touchless::DbusInterface::emitGestureDetected(const char *t_gestureName)
{
    m_daemonProxy->gesture_detected_signal.emit(t_gestureName);
}

void touchless::DbusInterface::setListener(touchless::DbusInterfaceListener *t_listener)
{
    m_listener = t_listener;
}

void touchless::DbusInterface::onNameOwned(const Glib::RefPtr<Gio::DBus::Connection> &t_connection,
                                           const Glib::ustring& t_name)
{
    if (m_daemonModeListener != nullptr)
    {
        m_daemonModeListener->onNameOwned();
    }
}

void touchless::DbusInterface::onNameLost(const Glib::RefPtr<Gio::DBus::Connection> &t_connection,
                                          const Glib::ustring& t_name)
{
    if (m_daemonModeListener != nullptr)
    {
        m_daemonModeListener->onNameLost();
    }
}

void touchless::DbusInterface::onBusConnect(const Glib::RefPtr<Gio::DBus::Connection> &t_connection,
                                            const Glib::ustring &t_name)
{
    if (m_daemonModeListener != nullptr)
    {
        m_daemonModeListener->onBusConnect();
    }
}

void touchless::DbusInterface::setDaemonModeListener(DbusInterfaceDaemonModeListener *t_daemonModeListener)
{
    m_daemonModeListener = t_daemonModeListener;
}
