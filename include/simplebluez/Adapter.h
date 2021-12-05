#pragma once

#include <simpledbus/advanced/Proxy.h>

#include <simplebluez/interfaces/Adapter1.h>

namespace SimpleBluez {

class Adapter : public SimpleDBus::Proxy {
  public:
    Adapter(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    ~Adapter();

    std::string identifier() const;
    std::string address();
    bool discovering();

  private:
    std::shared_ptr<SimpleDBus::Proxy> path_create(const std::string& path) override;
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name,
                                                             SimpleDBus::Holder options) override;

    std::shared_ptr<Adapter1> adapter1();
};

}  // namespace SimpleBluez
