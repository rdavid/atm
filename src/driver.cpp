// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#include <driver.hpp>

namespace atm
{
// https://bugs.llvm.org/show_bug.cgi?id=23728
// clang-format off

driver::driver() {
  m_interface.display_enter_card();
}

void driver::card_inserted(const std::string& account) {
  m_account = account;
  m_machine.handle(c_event_insert(), *this);
}

void driver::digit_pressed(char digit) {
  m_pass << digit;
  m_machine.handle(c_event_digit(), *this);
}

void driver::balance_pressed() {
  m_machine.handle(c_event_balance(), *this);
}

void driver::withdraw_pressed(unsigned amount) {
  m_amount = amount;
  m_machine.handle(c_event_withdraw(), *this);
}

void driver::cancel_pressed() {
  auto m1 = m_interface.display_cancelled();
  m1.wait();
  auto m2 = m_interface.eject_card();
  m_amount = 0;
  m_pass.str("");
  m_account.clear();
  m_machine.reset();
  m2.wait();
  m_interface.display_enter_card();
}

// clang-format on

} // namespace atm
