#include <simplebluez/Adapter.h>
#include <simplebluez/Device.h>

#include <simplebluez/interfaces/Adapter1.h>

#include <iostream>

using namespace SimpleBluez;

Adapter::Adapter(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
    : Proxy(conn, bus_name, path) {}

Adapter::~Adapter() {}

std::shared_ptr<SimpleDBus::Proxy> Adapter::path_create(const std::string& path) {
    std::cout << "Creating proxy for " << path << std::endl;

    auto child = std::make_shared<Device>(_conn, _bus_name, path);
    return std::static_pointer_cast<SimpleDBus::Proxy>(child);
}

std::shared_ptr<SimpleDBus::Interface> Adapter::interfaces_create(const std::string& interface_name,
                                                                       SimpleDBus::Holder options) {
    std::cout << "Creating interface " << interface_name << " for " << _path << std::endl;

    if (interface_name == "org.bluez.Adapter1") {
        return std::static_pointer_cast<SimpleDBus::Interface>(std::make_shared<Adapter1>(_conn, _path));
    }

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}
