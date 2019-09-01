static const char interfaceXml0[] = R"XML_DELIMITER(<!DOCTYPE node PUBLIC "-//freedesktop//DTD D-BUS Object Introspection 1.0//EN"
        "http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd">

<node name="/com/thelvm/touchless">
    <interface name="com.thelvm.touchless">
        <signal name="gesture_detected">
            <arg type="s" direction="out" name="gesture"/>
        </signal>
    </interface>
</node>
)XML_DELIMITER";

#include "touchless_gdbus_stub.h"

com::thelvm::touchlessStub::touchlessStub():
    m_interfaceName("com.thelvm.touchless")
{
    gesture_detected_signal.connect(sigc::mem_fun(this, &touchlessStub::gesture_detected_emitter));
}

com::thelvm::touchlessStub::~touchlessStub()
{
    unregister_object();
}

guint com::thelvm::touchlessStub::register_object(
    const Glib::RefPtr<Gio::DBus::Connection> &connection,
    const Glib::ustring &object_path)
{
    if (m_registeredObjectId != 0) {
        g_warning("Cannot register the same object (%s) twice", object_path.c_str());
        return 0;
    }

    try {
        introspection_data = Gio::DBus::NodeInfo::create_for_xml(interfaceXml0);
    } catch(const Glib::Error& ex) {
        g_warning("Unable to create introspection data for %s: %s", object_path.c_str(), ex.what().c_str());
        return 0;
    }
    Gio::DBus::InterfaceVTable *interface_vtable =
        new Gio::DBus::InterfaceVTable(
            sigc::mem_fun(this, &touchlessStub::on_method_call),
            sigc::mem_fun(this, &touchlessStub::on_interface_get_property),
            sigc::mem_fun(this, &touchlessStub::on_interface_set_property));

    try {
        m_registeredObjectId = connection->register_object(object_path,
            introspection_data->lookup_interface("com.thelvm.touchless"),
            *interface_vtable);
        m_connection = connection;
        m_objectPath = object_path;
    } catch(const Glib::Error &ex) {
        g_warning("Registration of object %s failed: %s", object_path.c_str(), ex.what().c_str());
    }

    return m_registeredObjectId;
}

void com::thelvm::touchlessStub::unregister_object()
{
    if (m_registeredObjectId == 0)
        return;

    m_connection->unregister_object(m_registeredObjectId);
    m_registeredObjectId = 0;
    m_connection.reset();
    m_objectPath.clear();
}

void com::thelvm::touchlessStub::on_method_call(
    const Glib::RefPtr<Gio::DBus::Connection> &/* connection */,
    const Glib::ustring &/* sender */,
    const Glib::ustring &/* object_path */,
    const Glib::ustring &/* interface_name */,
    const Glib::ustring &method_name,
    const Glib::VariantContainerBase &parameters,
    const Glib::RefPtr<Gio::DBus::MethodInvocation> &invocation)
{
    static_cast<void>(method_name); // maybe unused
    static_cast<void>(parameters); // maybe unused
    static_cast<void>(invocation); // maybe unused

}

void com::thelvm::touchlessStub::on_interface_get_property(
    Glib::VariantBase &property,
    const Glib::RefPtr<Gio::DBus::Connection> &/* connection */,
    const Glib::ustring &/* sender */,
    const Glib::ustring &/* object_path */,
    const Glib::ustring &/* interface_name */,
    const Glib::ustring &property_name)
{
    static_cast<void>(property); // maybe unused
    static_cast<void>(property_name); // maybe unused

}

bool com::thelvm::touchlessStub::on_interface_set_property(
    const Glib::RefPtr<Gio::DBus::Connection> &/* connection */,
    const Glib::ustring &/* sender */,
    const Glib::ustring &/* object_path */,
    const Glib::ustring &/* interface_name */,
    const Glib::ustring &property_name,
    const Glib::VariantBase &value)
{
    static_cast<void>(property_name); // maybe unused
    static_cast<void>(value); // maybe unused

    return true;
}

void com::thelvm::touchlessStub::gesture_detected_emitter(Glib::ustring gesture)
{
    std::vector<Glib::VariantBase> paramsList;

    paramsList.push_back(Glib::Variant<Glib::ustring>::create((gesture)));;

    m_connection->emit_signal(
        m_objectPath,
        "com.thelvm.touchless",
        "gesture_detected",
        Glib::ustring(),
        Glib::Variant<std::vector<Glib::VariantBase>>::create_tuple(paramsList));
}


bool com::thelvm::touchlessStub::emitSignal(
    const std::string &propName,
    Glib::VariantBase &value)
{
    std::map<Glib::ustring, Glib::VariantBase> changedProps;
    std::vector<Glib::ustring> changedPropsNoValue;

    changedProps[propName] = value;

    Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>> changedPropsVar =
        Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create(changedProps);
    Glib::Variant<std::vector<Glib::ustring>> changedPropsNoValueVar =
        Glib::Variant<std::vector<Glib::ustring>>::create(changedPropsNoValue);
    std::vector<Glib::VariantBase> ps;
    ps.push_back(Glib::Variant<Glib::ustring>::create(m_interfaceName));
    ps.push_back(changedPropsVar);
    ps.push_back(changedPropsNoValueVar);
    Glib::VariantContainerBase propertiesChangedVariant =
        Glib::Variant<std::vector<Glib::VariantBase>>::create_tuple(ps);

    m_connection->emit_signal(
        m_objectPath,
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        Glib::ustring(),
        propertiesChangedVariant);

    return true;
}
