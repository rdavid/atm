#pragma once

#include <atm_handler.hpp>
#include <bank_handler.hpp>
#include <interface_handler.hpp>
#include <string>

namespace atm
{

class driver
{
public:
  void digit_pressed(char digit);
  void balance_pressed();
  void withdraw_pressed(unsigned amount);
  void card_inserted(const std::string& account);
  void cancel_pressed();

private:
  interface_handler m_interface;
  bank_handler m_bank;
  atm_handler m_atm;
};

} // namespace atm