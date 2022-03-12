#include <simplebluez/Agent.h>

#include <iostream>

using namespace SimpleBluez;

Agent::Agent(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
    : Proxy(conn, bus_name, path) {
    std::cout << "Agent::Agent()" << std::endl;
}

std::string Agent::capabilities() { return "DisplayOnly"; }

std::shared_ptr<SimpleDBus::Interface> Agent::interfaces_create(const std::string& interface_name) {
    std::cout << "Agent interface created!: " << interface_name << std::endl;
    auto interface = std::make_shared<SimpleDBus::Interface>(_conn, _bus_name, _path, interface_name);
    return std::static_pointer_cast<SimpleDBus::Interface>(interface);
}
