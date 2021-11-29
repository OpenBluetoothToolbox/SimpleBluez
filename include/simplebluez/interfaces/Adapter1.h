#pragma once

#include <simpledbus/advanced/Interface.h>

namespace SimpleBluez {

#include <string>

class Adapter1 : public SimpleDBus::Interface {
  public:
    Adapter1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path);
    ~Adapter1();

    void StartDiscovery();
    void StopDiscovery();
    void SetDiscoveryFilter(SimpleDBus::Holder properties);
    SimpleDBus::Holder GetDiscoveryFilters();
    // void RemoveDevice(SimpleDBus::Holder device); // TODO: Implement

    // ----- PROPERTIES -----
    bool Discovering();
    std::string Address();

  protected:
    bool _discovering;
    std::string _address;
};

}  // namespace SimpleBluez
