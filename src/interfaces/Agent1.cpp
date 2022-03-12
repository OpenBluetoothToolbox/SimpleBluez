#include "simplebluez/interfaces/Agent1.h"

using namespace SimpleBluez;

#include <iostream>

Agent1::Agent1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path)
    : SimpleDBus::Interface(conn, "org.bluez", path, "org.bluez.Agent1") {}

void Agent1::message_handle(SimpleDBus::Message msg) {
    std::cout << "Received message: " << msg.to_string() << std::endl;
}
