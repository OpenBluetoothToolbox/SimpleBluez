#include "simplebluez/interfaces/Device1.h"

using namespace SimpleBluez;

Device1::Device1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path)
    : SimpleDBus::Interface(conn, "org.bluez", path, "org.bluez.Device1") {}

Device1::~Device1() {}

int16_t Device1::RSSI() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    property_refresh("RSSI");
    return _properties["RSSI"].get_int16();
}

std::string Device1::Address() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    property_refresh("Address");
    return _properties["Address"].get_string();
}

std::string Device1::Alias() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    property_refresh("Alias");
    return _properties["Alias"].get_string();
}

std::string Device1::Name() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    property_refresh("Name");
    return _properties["Name"].get_string();
}

std::map<uint16_t, std::vector<uint8_t>> Device1::ManufacturerData() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    property_refresh("ManufacturerData");
    // Use the locally cached version to avoid parsing the map multiple times.
    return _manufacturer_data;
}

bool Device1::Connected() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    property_refresh("Connected");
    return _properties["Connected"].get_boolean();
}

bool Device1::ServicesResolved() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    property_refresh("ServicesResolved");
    return _properties["ServicesResolved"].get_boolean();
}

void Device1::property_changed(std::string option_name) {
    if (option_name == "ManufacturerData") {
        _manufacturer_data.clear();
        std::map<uint16_t, SimpleDBus::Holder> manuf_data = _properties["ManufacturerData"].get_dict_uint16();
        // Loop through all received keys and store them.
        for (auto& [key, value_array] : manuf_data) {
            std::vector<uint8_t> raw_manuf_data;
            for (auto& elem : value_array.get_array()) {
                raw_manuf_data.push_back(elem.get_byte());
            }
            _manufacturer_data[key] = raw_manuf_data;
        }
    }
}
