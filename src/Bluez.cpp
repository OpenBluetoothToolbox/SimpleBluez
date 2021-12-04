#include <simplebluez/Bluez.h>
#include <simplebluez/ProxyOrg.h>
#include <simpledbus/interfaces/ObjectManager.h>

#include <iostream>

using namespace SimpleBluez;

Bluez::Bluez() : Proxy(std::make_shared<SimpleDBus::Connection>(DBUS_BUS_SYSTEM), "org.bluez", "/") {
    _interfaces["org.freedesktop.DBus.ObjectManager"] = std::static_pointer_cast<SimpleDBus::Interface>(
        std::make_shared<SimpleDBus::ObjectManager>(_conn, "org.bluez", "/"));

    // object_manager.InterfacesAdded = [&](std::string path, SimpleDBus::Holder options) { add_path(path, options); };
    // object_manager.InterfacesRemoved = [&](std::string path, SimpleDBus::Holder options) {
    //     remove_path(path, options);
    // };
}

Bluez::~Bluez() { _conn->remove_match("type='signal',sender='org.bluez'"); }

void Bluez::init() {
    _conn->init();

    // Load all managed objects
    SimpleDBus::Holder managed_objects = object_manager()->GetManagedObjects();
    for (auto& [path, managed_interfaces] : managed_objects.get_dict_object_path()) {
        path_add(path, managed_interfaces);
    }

    _conn->add_match("type='signal',sender='org.bluez'");
}

void Bluez::run_async() {
    _conn->read_write();
    SimpleDBus::Message message = _conn->pop_message();
    while (message.is_valid()) {
        message_forward(message);
        message = _conn->pop_message();
    }
}

std::vector<std::shared_ptr<Adapter>> Bluez::get_adapters() {
    if (children().find("/org") == children().end()) {
        // TODO: throw exception
        return {};
    }

    return std::dynamic_pointer_cast<ProxyOrg>(children().at("/org"))->get_adapters();
}

std::shared_ptr<SimpleDBus::Proxy> Bluez::path_create(const std::string& path) {
    auto child = std::make_shared<ProxyOrg>(_conn, _bus_name, path);
    return std::static_pointer_cast<SimpleDBus::Proxy>(child);
}

std::shared_ptr<SimpleDBus::Interface> Bluez::interfaces_create(const std::string& interface_name,
                                                                     SimpleDBus::Holder options) {
    std::cout << "Creating interface " << interface_name << "for " << _path << std::endl;
    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}

std::shared_ptr<SimpleDBus::ObjectManager> Bluez::object_manager() {
    if (_interfaces.find("org.freedesktop.DBus.ObjectManager") == _interfaces.end()) {
        return nullptr;
    }

    return std::dynamic_pointer_cast<SimpleDBus::ObjectManager>(_interfaces["org.freedesktop.DBus.ObjectManager"]);
}
