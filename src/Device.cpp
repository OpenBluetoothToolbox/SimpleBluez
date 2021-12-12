#include <simplebluez/Device.h>
#include <simplebluez/Service.h>

#include <iostream>

using namespace SimpleBluez;

Device::Device(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
    : Proxy(conn, bus_name, path) {}

Device::~Device() {}

std::shared_ptr<SimpleDBus::Proxy> Device::path_create(const std::string& path) {
    auto child = std::make_shared<Service>(_conn, _bus_name, path);
    return std::static_pointer_cast<SimpleDBus::Proxy>(child);
}

std::shared_ptr<SimpleDBus::Interface> Device::interfaces_create(const std::string& interface_name) {
    if (interface_name == "org.bluez.Device1") {
        return std::static_pointer_cast<SimpleDBus::Interface>(std::make_shared<Device1>(_conn, _path));
    }

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}

std::shared_ptr<Device1> Device::device1() {
    if (_interfaces.find("org.bluez.Device1") == _interfaces.end()) {
        // TODO: throw exception
        return nullptr;
    }

    return std::dynamic_pointer_cast<Device1>(_interfaces.at("org.bluez.Device1"));
}

std::vector<std::shared_ptr<Service>> Device::services() {
    std::vector<std::shared_ptr<Service>> services;

    for (auto& [path, child] : _children) {
        auto service = std::dynamic_pointer_cast<Service>(child);
        if (service) {
            services.push_back(service);
        }
    }
    return services;
}

void Device::connect() { device1()->Connect(); }

void Device::disconnect() { device1()->Disconnect(); }

std::string Device::address() { return device1()->Address(); }

std::string Device::name() { return device1()->Name(); }

std::string Device::alias() { return device1()->Alias(); }

std::map<uint16_t, std::vector<uint8_t>> Device::manufacturer_data() { return device1()->ManufacturerData(); }

bool Device::connected() { return device1()->Connected(); }

bool Device::services_resolved() { return device1()->ServicesResolved(); }
