#pragma once

#include <interface.hpp>

namespace atm
{

class interface_handler
{
 public:
  const interface& get() const {
    return m_interface;
  }

 private:
  interface m_interface;
};

} // namespace atm
