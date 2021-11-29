#pragma once

#include "simpledbus/SimpleDBus.h"

#include "GattCharacteristic1.h"

#include <string>

class BluezGattCharacteristic : public GattCharacteristic1 {
  private:
    std::shared_ptr<SimpleDBus::Connection> _conn;
    std::string _path;

    void add_interface(std::string interface_name, SimpleDBus::Holder options);

  public:
    BluezGattCharacteristic(std::shared_ptr<SimpleDBus::Connection> conn, std::string path, SimpleDBus::Holder options);
    ~BluezGattCharacteristic();

    bool add_path(std::string path, SimpleDBus::Holder options);
    bool remove_path(std::string path, SimpleDBus::Holder options);
    bool process_received_signal(SimpleDBus::Message& message);
};
