// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#pragma once

#include <atm_handler.hpp>
#include <bank_handler.hpp>
#include <interface_handler.hpp>
#include <machine.hpp>
#include <string>
#include <sstream>

namespace atm
{

class driver {
 public:
  driver();
  void digit_pressed(char digit);
  void balance_pressed();
  void withdraw_pressed(unsigned amount);
  void card_inserted(const std::string& account);
  void cancel_pressed();
 private:
  // Keeps add data at driver. The states need to have access to the data, use
  // friend feature. TODO: consider more elegant solution.
  friend class c_state_init;
  friend class c_state_card_in;
  friend class c_state_pin_ok;
  friend class c_state_withdraw;
  interface_handler m_interface;
  bank_handler m_bank;
//  atm_handler m_atm;
  c_machine m_machine;
  unsigned m_amount;
  std::string m_account;
  std::stringstream m_pass;
};

} // namespace atm
