#include <simplebluez/Agent.h>
#include <simplebluez/interfaces/Agent1.h>

#include <iostream>

using namespace SimpleBluez;

Agent::Agent(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
    : Proxy(conn, bus_name, path) {
    _interfaces.emplace(std::make_pair(
        "org.bluez.Agent1", std::static_pointer_cast<SimpleDBus::Interface>(std::make_shared<Agent1>(_conn, _path))));
    std::cout << "Agent::Agent()" << std::endl;
}

std::string Agent::capabilities() { return "DisplayOnly"; }
