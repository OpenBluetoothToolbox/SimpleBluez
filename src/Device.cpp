#include <simplebluez/Device.h>
#include <simplebluez/Service.h>

#include <simplebluez/interfaces/Device1.h>

#include <iostream>

using namespace SimpleBluez;

Device::Device(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
    : Proxy(conn, bus_name, path) {}

Device::~Device() {}

std::shared_ptr<SimpleDBus::Proxy> Device::path_create(const std::string& path) {
    std::cout << "Creating proxy for " << path << std::endl;

    auto child = std::make_shared<Service>(_conn, _bus_name, path);
    return std::static_pointer_cast<SimpleDBus::Proxy>(child);
}

std::shared_ptr<SimpleDBus::Interface> Device::interfaces_create(const std::string& interface_name,
                                                                 SimpleDBus::Holder options) {
    if (interface_name == "org.bluez.Device1") {
        return std::static_pointer_cast<SimpleDBus::Interface>(std::make_shared<Device1>(_conn, _path));
    }

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}
