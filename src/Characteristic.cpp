#include <simplebluez/Characteristic.h>

#include <iostream>

using namespace SimpleBluez;

Characteristic::Characteristic(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name,
                               const std::string& path)
    : Proxy(conn, bus_name, path) {}

Characteristic::~Characteristic() {}

std::shared_ptr<SimpleDBus::Interface> Characteristic::interfaces_create(const std::string& interface_name) {
    if (interface_name == "org.bluez.GattCharacteristic1") {
        return std::static_pointer_cast<SimpleDBus::Interface>(std::make_shared<GattCharacteristic1>(_conn, _path));
    }

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}

std::shared_ptr<GattCharacteristic1> Characteristic::gattcharacteristic1() {
    if (_interfaces.find("org.bluez.GattCharacteristic1") == _interfaces.end()) {
        // TODO: throw exception
        return nullptr;
    }

    return std::dynamic_pointer_cast<GattCharacteristic1>(_interfaces.at("org.bluez.GattCharacteristic1"));
}

std::string Characteristic::uuid() { return gattcharacteristic1()->UUID(); }
