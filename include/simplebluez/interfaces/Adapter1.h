#pragma once

#include <simpledbus/advanced/Interface.h>

#include <optional>
#include <string>
#include <vector>

namespace SimpleBluez {

class Adapter1 : public SimpleDBus::Interface {
  public:
    typedef enum { AUTO, BREDR, LE } DiscoveryFilterTransport;
  
    struct DiscoveryFilter {
      std::vector<std::string> UUIDs = {};
      std::optional<int16_t> RSSI;
      std::optional<uint16_t> Pathloss;
      DiscoveryFilterTransport Transport = DiscoveryFilterTransport::AUTO;
      bool DuplicateData = true;
      bool Discoverable = false;
      std::string Pattern = "";
    };

    Adapter1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path);
    virtual ~Adapter1() = default;

    // ----- METHODS -----
    void RemoveDevice(std::string device_path);
    void StartDiscovery();
    void StopDiscovery();
    void SetDiscoveryFilter(DiscoveryFilter filter);
    SimpleDBus::Holder GetDiscoveryFilters();
    // void RemoveDevice(SimpleDBus::Holder device); // TODO: Implement

    // ----- PROPERTIES -----
    bool Discovering(bool refresh = true);
    std::string Address();

  protected:
    bool _discovering;
    std::string _address;

    void property_changed(std::string option_name) override;
};

}  // namespace SimpleBluez
