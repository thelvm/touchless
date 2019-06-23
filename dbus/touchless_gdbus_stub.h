#pragma once
#include <string>
#include <vector>
#include <glibmm.h>
#include <giomm.h>
#include "touchless_gdbus_common.h"

namespace touchless {

class daemonStub : public sigc::trackable {
public:
    daemonStub();
    virtual ~daemonStub();

    daemonStub(const daemonStub &other) = delete;
    daemonStub(daemonStub &&other) = delete;
    daemonStub &operator=(const daemonStub &other) = delete;
    daemonStub &operator=(daemonStub &&other) = delete;

    guint register_object(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                          const Glib::ustring &object_path);
    void unregister_object();

    int usage_count() const {
        return m_registeredObjectId == 0 ? 0 : 1;
    }

    class MethodInvocation;

protected:

    void gesture_detected_emitter(Glib::ustring);
    sigc::signal<void, Glib::ustring> gesture_detected_signal;

    void on_method_call(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                        const Glib::ustring &sender,
                        const Glib::ustring &object_path,
                        const Glib::ustring &interface_name,
                        const Glib::ustring &method_name,
                        const Glib::VariantContainerBase &parameters,
                        const Glib::RefPtr<Gio::DBus::MethodInvocation> &invocation);

    void on_interface_get_property(Glib::VariantBase& property,
                                   const Glib::RefPtr<Gio::DBus::Connection> &connection,
                                   const Glib::ustring &sender,
                                   const Glib::ustring &object_path,
                                   const Glib::ustring &interface_name,
                                   const Glib::ustring &property_name);

    bool on_interface_set_property(
        const Glib::RefPtr<Gio::DBus::Connection> &connection,
        const Glib::ustring &sender,
        const Glib::ustring &object_path,
        const Glib::ustring &interface_name,
        const Glib::ustring &property_name,
        const Glib::VariantBase &value);

private:
    bool emitSignal(const std::string &propName, Glib::VariantBase &value);

    Glib::RefPtr<Gio::DBus::NodeInfo> introspection_data;
    Glib::RefPtr<Gio::DBus::Connection> m_connection;
    guint m_registeredObjectId = 0;
    std::string m_objectPath;
    std::string m_interfaceName;
};

class daemonStub::MethodInvocation {
public:
    MethodInvocation(const Glib::RefPtr<Gio::DBus::MethodInvocation> &msg):
        m_message(msg) {}

    const Glib::RefPtr<Gio::DBus::MethodInvocation> getMessage() {
        return m_message;
    }

    void ret(Glib::Error error) {
        m_message->return_error(error);
    }

    void returnError(const Glib::ustring &domain, int code, const Glib::ustring &message) {
        m_message->return_error(domain, code, message);
    }

private:
    Glib::RefPtr<Gio::DBus::MethodInvocation> m_message;
};

} // touchless

