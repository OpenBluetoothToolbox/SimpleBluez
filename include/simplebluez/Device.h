#pragma once 

#include <simpledbus/advanced/Proxy.h>

namespace SimpleBluez {

class Device : public SimpleDBus::Proxy {
  public:
    Device(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    ~Device();

  private:
    std::shared_ptr<SimpleDBus::Proxy> path_create(const std::string& path) override;
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name,
                                                                  SimpleDBus::Holder options) override;
};

}  // namespace SimpleBluez
