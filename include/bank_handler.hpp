#pragma once

#include <bank.hpp>

namespace atm
{

class bank_handler {
 public:
   bank& get() {
       return m_bank;
   }
  /* PUT YOUR CODE HERE */
private:
  bank m_bank;
};

} // namespace atm
