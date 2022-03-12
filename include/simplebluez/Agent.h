#pragma once

#include <simpledbus/advanced/Proxy.h>

namespace SimpleBluez {

class Agent : public SimpleDBus::Proxy {
  // TODO: Define enum for capabilities

  public:
    Agent(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    virtual ~Agent() = default;

    virtual std::string capabilities();

  private:
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name) override;
};

}  // namespace SimpleBluez
