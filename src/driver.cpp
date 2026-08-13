// SPDX-FileCopyrightText: 2020-2026 David Rabkin
// SPDX-License-Identifier: 0BSD
#include <driver.hpp>
#include <string>

// driver.cpp - driver implementation for the ATM. Coordinates input events
// from the test harness with the ATM state machine and the bank/interface
// backends. Methods intentionally perform small synchronous waits where
// necessary to ensure proper UI sequencing.

namespace atm
{
// See https://bugs.llvm.org/show_bug.cgi?id=23728
// clang-format off

// Shows the initial prompt asking the user to insert a card.
driver::driver() : m_interface() {
  m_interface.display_enter_card();
}

// Handles card insertion by setting the active account and dispatching the
// insert event to the state machine.
void driver::card_inserted(const std::string& account) {
  m_account = account;
  m_machine.handle(c_event_insert(), *this);
}

// Handles PIN digit entry by appending the digit to the working PIN buffer
// and notifying the state machine so it can decide the next action.
void driver::digit_pressed(char digit) {
  m_pass << digit;
  m_machine.handle(c_event_digit(), *this);
}

// Requests balance display by forwarding the balance event to the state
// machine, which queries the bank and renders the result when available.
void driver::balance_pressed() {
  m_machine.handle(c_event_balance(), *this);
}

// Requests withdrawal of a fixed amount by setting the amount and signaling
// the state machine, which performs the withdrawal and UI issuance.
void driver::withdraw_pressed(unsigned amount) {
  m_amount = amount;
  m_machine.handle(c_event_withdraw(), *this);
}

// Cancels the current operation by displaying the cancellation message,
// ejecting the card, resetting internal state (amount, PIN buffer, account),
// and resetting the state machine.
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
