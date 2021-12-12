#pragma once

#include <simpledbus/advanced/Proxy.h>

namespace SimpleBluez {

class Characteristic : public SimpleDBus::Proxy {
  public:
    Characteristic(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    ~Characteristic();

  private:
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name) override;
};

}  // namespace SimpleBluez
