#pragma once

#include <simpledbus/advanced/Proxy.h>

#include <simplebluez/Service.h>
#include <simplebluez/interfaces/Device1.h>

namespace SimpleBluez {

class Device : public SimpleDBus::Proxy {
  public:
    Device(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    ~Device();

    // ----- PROPERTIES -----
    std::vector<std::shared_ptr<Service>> services();

    std::string address();
    std::string name();
    std::string alias();

    std::map<uint16_t, std::vector<uint8_t>> manufacturer_data();

    bool connected();
    bool services_resolved();

    // ----- METHODS -----
    void connect();
    void disconnect();

  private:
    std::shared_ptr<SimpleDBus::Proxy> path_create(const std::string& path) override;
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name) override;

    std::shared_ptr<Device1> device1();
};

}  // namespace SimpleBluez
