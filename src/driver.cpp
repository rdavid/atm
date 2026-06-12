// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#include <driver.hpp>

// driver.cpp - driver implementation for the ATM. Coordinates input events
// from the test harness with the ATM state machine and the bank/interface
// backends. Methods intentionally perform small synchronous waits where
// necessary to ensure proper UI sequencing.

namespace atm
{
// See https://bugs.llvm.org/show_bug.cgi?id=23728
// clang-format off

// Constructor: show initial prompt asking user to insert a card.
driver::driver() {
  m_interface.display_enter_card();
}

// Handle card insertion: set the active account and dispatch the insert event
// to the state machine.
void driver::card_inserted(const std::string& account) {
  m_account = account;
  m_machine.handle(c_event_insert(), *this);
}

// Handle PIN digit entry: append digit to the working PIN buffer and
// notify the state machine so it can decide next actions.
void driver::digit_pressed(char digit) {
  m_pass << digit;
  m_machine.handle(c_event_digit(), *this);
}

// Request to display balance: forward the balance event to the state
// machine which will query the bank and render the result when available.
void driver::balance_pressed() {
  m_machine.handle(c_event_balance(), *this);
}

// Request to withdraw a fixed amount: set amount and signal the state
// machine. The state machine performs the withdrawal and UI issuance.
void driver::withdraw_pressed(unsigned amount) {
  m_amount = amount;
  m_machine.handle(c_event_withdraw(), *this);
}

// Cancel the current operation: display cancellation, eject card, reset
// internal state (amount, PIN buffer, account) and reset the state machine.
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
