#include "simplebluez/interfaces/Device1.h"

using namespace SimpleBluez;

Device1::Device1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path)
    : SimpleDBus::Interface(conn, "org.bluez", path, "org.bluez.Device1") {}

Device1::~Device1() {}

void Device1::property_changed(std::string option_name, SimpleDBus::Holder value) {}

void Device1::property_removed(std::string option_name) {}
