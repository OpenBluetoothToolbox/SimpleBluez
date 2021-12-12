#pragma once

#include <simpledbus/advanced/Proxy.h>

namespace SimpleBluez {

class Service : public SimpleDBus::Proxy {
  public:
    Service(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    ~Service();

  private:
    std::shared_ptr<SimpleDBus::Proxy> path_create(const std::string& path) override;
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name) override;
};

}  // namespace SimpleBluez
