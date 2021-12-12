#pragma once

#include <simpledbus/advanced/Proxy.h>

#include <simplebluez/interfaces/GattCharacteristic1.h>

namespace SimpleBluez {

class Characteristic : public SimpleDBus::Proxy {
  public:
    Characteristic(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    ~Characteristic();

    // ----- PROPERTIES -----
    std::string uuid();

  private:
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name) override;

    std::shared_ptr<GattCharacteristic1> gattcharacteristic1();
};

}  // namespace SimpleBluez
