#include <simplebluez/Characteristic.h>
#include <simplebluez/Service.h>

#include <iostream>

using namespace SimpleBluez;

Service::Service(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
    : Proxy(conn, bus_name, path) {}

Service::~Service() {}

std::shared_ptr<SimpleDBus::Proxy> Service::path_create(const std::string& path) {
    auto child = std::make_shared<Characteristic>(_conn, _bus_name, path);
    return std::static_pointer_cast<SimpleDBus::Proxy>(child);
}

std::shared_ptr<SimpleDBus::Interface> Service::interfaces_create(const std::string& interface_name) {
    if (interface_name == "org.bluez.GattService1") {
        return std::static_pointer_cast<SimpleDBus::Interface>(std::make_shared<GattService1>(_conn, _path));
    }

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}

std::shared_ptr<GattService1> Service::gattservice1() {
    if (_interfaces.find("org.bluez.GattService1") == _interfaces.end()) {
        // TODO: throw exception
        return nullptr;
    }

    return std::dynamic_pointer_cast<GattService1>(_interfaces.at("org.bluez.GattService1"));
}

std::string Service::uuid() { return gattservice1()->UUID(); }

std::vector<std::shared_ptr<Characteristic>> Service::characteristics() {
    std::vector<std::shared_ptr<Characteristic>> characteristics;

    for (auto& [path, child] : _children) {
        auto characteristic = std::dynamic_pointer_cast<Characteristic>(child);
        if (characteristic) {
            characteristics.push_back(characteristic);
        }
    }
    return characteristics;
}
