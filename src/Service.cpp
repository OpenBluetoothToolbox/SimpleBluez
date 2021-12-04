#include <simplebluez/Characteristic.h>
#include <simplebluez/Service.h>

#include <iostream>

using namespace SimpleBluez;

Service::Service(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
    : Proxy(conn, bus_name, path) {}

Service::~Service() {}

std::shared_ptr<SimpleDBus::Proxy> Service::path_create(const std::string& path) {
    std::cout << "Creating proxy for " << path << std::endl;

    auto child = std::make_shared<Characteristic>(_conn, _bus_name, path);
    return std::static_pointer_cast<SimpleDBus::Proxy>(child);
}

std::shared_ptr<SimpleDBus::Interface> Service::interfaces_create(const std::string& interface_name,
                                                                       SimpleDBus::Holder options) {
    std::cout << "Creating interface " << interface_name << " for " << _path << std::endl;

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}
