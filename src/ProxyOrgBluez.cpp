#include <simplebluez/Adapter.h>
#include <simplebluez/ProxyOrgBluez.h>

#include <iostream>

using namespace SimpleBluez;

ProxyOrgBluez::ProxyOrgBluez(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name,
                             const std::string& path)
    : Proxy(conn, bus_name, path) {}

ProxyOrgBluez::~ProxyOrgBluez() {}

std::shared_ptr<SimpleDBus::Proxy> ProxyOrgBluez::path_create(const std::string& path) {
    std::cout << "Creating proxy for " << path << std::endl;

    auto child = std::make_shared<Adapter>(_conn, _bus_name, path);
    return std::static_pointer_cast<SimpleDBus::Proxy>(child);
}

std::shared_ptr<SimpleDBus::Interface> ProxyOrgBluez::interfaces_create(const std::string& interface_name,
                                                                             SimpleDBus::Holder options) {
    std::cout << "Creating interface " << interface_name << " for " << _path << std::endl;

    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}

std::vector<std::shared_ptr<Adapter>> ProxyOrgBluez::get_adapters() {
    std::vector<std::shared_ptr<Adapter>> adapters;

    for (auto& [path, child] : _children) {
        auto adapter = std::dynamic_pointer_cast<Adapter>(child);
        if (adapter) {
            adapters.push_back(adapter);
        }
    }
    return adapters;
}
