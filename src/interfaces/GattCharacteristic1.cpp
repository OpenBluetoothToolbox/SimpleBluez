#include "simplebluez/interfaces/GattCharacteristic1.h"

using namespace SimpleBluez;

GattCharacteristic1::GattCharacteristic1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path)
    : SimpleDBus::Interface(conn, "org.bluez", path, "org.bluez.GattService1") {}

GattCharacteristic1::~GattCharacteristic1() {}

std::string GattCharacteristic1::UUID() {
    // As the UUID property doesn't change, we can cache it
    return _uuid;
}

void GattCharacteristic1::property_changed(std::string option_name) {
    if (option_name == "UUID") {
        _uuid = _properties["UUID"].get_string();
    }
}
