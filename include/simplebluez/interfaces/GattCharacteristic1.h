#pragma once

#include <simpledbus/advanced/Interface.h>

#include <string>

namespace SimpleBluez {

class GattCharacteristic1 : public SimpleDBus::Interface {
  public:
    GattCharacteristic1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path);
    ~GattCharacteristic1();

    // ----- METHODS -----

    // ----- PROPERTIES -----
    std::string UUID();

  protected:
    void property_changed(std::string option_name) override;

    std::string _uuid;
};

}  // namespace SimpleBluez
