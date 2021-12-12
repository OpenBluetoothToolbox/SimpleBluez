#include <simplebluez/Characteristic.h>

#include <iostream>

using namespace SimpleBluez;

Characteristic::Characteristic(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name,
                               const std::string& path)
    : Proxy(conn, bus_name, path) {}

Characteristic::~Characteristic() {}

std::shared_ptr<SimpleDBus::Interface> Characteristic::interfaces_create(const std::string& interface_name) {
    std::cout << "Creating interface " << interface_name << " for " << _path << std::endl;

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}
