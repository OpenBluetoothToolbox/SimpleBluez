#include "simplebluez/interfaces/Adapter1.h"

using namespace SimpleBluez;

Adapter1::Adapter1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path)
    : SimpleDBus::Interface(conn, "org.bluez", path, "org.bluez.Adapter1") {}

Adapter1::~Adapter1() {}

void Adapter1::StartDiscovery() {
    auto msg = create_method_call("StartDiscovery");
    _conn->send_with_reply_and_block(msg);
}

void Adapter1::StopDiscovery() {
    auto msg = create_method_call("StopDiscovery");
    _conn->send_with_reply_and_block(msg);
    // NOTE: It might take a few seconds until the peripheral reports that is has actually stopped discovering.
}

SimpleDBus::Holder Adapter1::GetDiscoveryFilters() {
    auto msg = create_method_call("GetDiscoveryFilters");
    SimpleDBus::Message reply_msg = _conn->send_with_reply_and_block(msg);
    SimpleDBus::Holder discovery_filters = reply_msg.extract();
    return discovery_filters;
}

void Adapter1::SetDiscoveryFilter(SimpleDBus::Holder properties) {
    auto msg = create_method_call("SetDiscoveryFilter");
    msg.append_argument(properties, "a{sv}");
    _conn->send_with_reply_and_block(msg);
}

bool Adapter1::Discovering() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    if (_loaded) {
        auto value = property_get("Discovering");
        property_changed("Discovering", value);
    }
    return _discovering;
}

std::string Adapter1::Address() {
    std::lock_guard<std::recursive_mutex> lock(_property_update_mutex);
    if (_loaded) {
        auto value = property_get("Address");
        property_changed("Address", value);
    }
    return _address;
}

void Adapter1::property_changed(std::string option_name, SimpleDBus::Holder value) {
    if (option_name == "Discovering") {
        _discovering = value.get_boolean();
    } else if (option_name == "Address") {
        _address = value.get_string();
    }
}

void Adapter1::property_removed(std::string option_name) {}
