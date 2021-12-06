#pragma once

#include <simpledbus/advanced/Interface.h>

#include <string>

namespace SimpleBluez {

class Device1 : public SimpleDBus::Interface {
  public:
    Device1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path);
    ~Device1();

    // ----- METHODS -----

    // ----- PROPERTIES -----

  protected:
    void property_changed(std::string option_name, SimpleDBus::Holder value) override;
    void property_removed(std::string option_name) override;
};

}  // namespace SimpleBluez
