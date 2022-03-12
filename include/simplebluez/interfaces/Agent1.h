#pragma once

#include <simpledbus/advanced/Interface.h>

#include <string>

namespace SimpleBluez {

class Agent1 : public SimpleDBus::Interface {
  public:

    Agent1(std::shared_ptr<SimpleDBus::Connection> conn, std::string path);
    virtual ~Agent1() = default;

    // ----- METHODS -----

    // ----- PROPERTIES -----

  protected:

  void message_handle(SimpleDBus::Message msg) override;

};

}  // namespace SimpleBluez
