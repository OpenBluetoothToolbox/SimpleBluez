#include <simplebluez/Adapter.h>
#include <simplebluez/Device.h>

#include <simplebluez/interfaces/Adapter1.h>

#include <iostream>

using namespace SimpleBluez;

Adapter::Adapter(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
    : Proxy(conn, bus_name, path) {}

Adapter::~Adapter() {}

std::shared_ptr<SimpleDBus::Proxy> Adapter::path_create(const std::string& path) {
    auto child = std::make_shared<Device>(_conn, _bus_name, path);
    return std::static_pointer_cast<SimpleDBus::Proxy>(child);
}

std::shared_ptr<SimpleDBus::Interface> Adapter::interfaces_create(const std::string& interface_name) {
    if (interface_name == "org.bluez.Adapter1") {
        return std::static_pointer_cast<SimpleDBus::Interface>(std::make_shared<Adapter1>(_conn, _path));
    }

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}

std::shared_ptr<Adapter1> Adapter::adapter1() {
    if (_interfaces.find("org.bluez.Adapter1") == _interfaces.end()) {
        // TODO: throw exception
        return nullptr;
    }

    return std::dynamic_pointer_cast<Adapter1>(_interfaces.at("org.bluez.Adapter1"));
}

std::string Adapter::identifier() const {
    std::size_t start = _path.find_last_of("/");
    return _path.substr(start + 1);
}

std::string Adapter::address() { return adapter1()->Address(); }

bool Adapter::discovering() { return adapter1()->Discovering(); }

void Adapter::discovery_filter(const DiscoveryFilter& filter) { adapter1()->SetDiscoveryFilter(filter); }

void Adapter::discovery_start() { adapter1()->StartDiscovery(); }

void Adapter::discovery_stop() { adapter1()->StopDiscovery(); }

std::shared_ptr<Device> Adapter::device_get(const std::string& path) {
    if (_children.find(path) == _children.end()) {
        // TODO: throw exception
        return nullptr;
    }

    return std::dynamic_pointer_cast<Device>(_children.at(path));
}

void Adapter::set_on_device_updated(std::function<void(std::shared_ptr<Device> device)> callback) {
    on_child_signal_received.load([this, callback](std::string child_path) {
        auto device = device_get(child_path);
        if (device) {
            callback(device);
        }
    });
}
