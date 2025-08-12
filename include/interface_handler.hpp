// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#pragma once

#include <interface.hpp>
#include <future>

namespace atm
{

class interface_handler {
 public:
  std::future<void> issue_money(unsigned amount) const {
    return std::async(&interface::issue_money, &m_interface, amount);
  }
  std::future<void> display_insufficient_funds() const {
    return std::async(&interface::display_insufficient_funds, &m_interface);
  }
  std::future<void> display_enter_pin() const {
    return std::async(&interface::display_enter_pin, &m_interface);
  }
  std::future<void> display_enter_card() const {
    return std::async(&interface::display_enter_card, &m_interface);
  }
  std::future<void> display_balance(unsigned balance) const {
    return std::async(&interface::display_balance, &m_interface, balance);
  }
  std::future<void> display_withdrawal_options() const {
    return std::async(&interface::display_withdrawal_options, &m_interface);
  }
  std::future<void> display_cancelled() const {
    return std::async(&interface::display_cancelled, &m_interface);
  }
  std::future<void> display_pin_incorrect_message() const {
    return std::async(&interface::display_pin_incorrect_message, &m_interface);
  }
  std::future<void> eject_card() const {
    return std::async(&interface::eject_card, &m_interface);
  }
 private:
  interface m_interface;
};

}  // namespace atm
