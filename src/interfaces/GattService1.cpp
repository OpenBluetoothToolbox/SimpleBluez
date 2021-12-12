#include "simplebluez/interfaces/GattService1.h"

using namespace SimpleBluez;

GattService1::GattService1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path)
    : SimpleDBus::Interface(conn, "org.bluez", path, "org.bluez.GattService1") {}

GattService1::~GattService1() {}

std::string GattService1::UUID() {
    // As the UUID property doesn't change, we can cache it
    return _uuid;
}

#include <iostream>

void GattService1::property_changed(std::string option_name) {
    std::cout << "GattService1::property_changed: " << option_name << std::endl;

    if (option_name == "UUID") {
        _uuid = _properties["UUID"].get_string();
    }
}
