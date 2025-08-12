// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#pragma once
#include <iostream>

namespace atm
{
class interface
{
public:
  void issue_money(unsigned amount) const { std::cout << "Issuing " << amount << '\n'; }
  void display_insufficient_funds() const { std::cout << "Insufficient funds\n"; }
  void display_enter_pin() const { std::cout << "Please enter your PIN (0-9)\n"; }
  void display_enter_card() const { std::cout << "Please enter your card (i)\n"; }
  void display_balance(unsigned balance) const
  {
    std::cout << "The balance of your account is " << balance << '\n';
  }
  void display_withdrawal_options() const
  {
    std::cout << "Withdraw 50? (w)\n";
    std::cout << "Display Balance? (b)\n";
    std::cout << "Cancel? (c)\n";
  }
  void display_cancelled() const { std::cout << "Cancelled\n"; }
  void display_pin_incorrect_message() const { std::cout << "PIN incorrect\n"; }
  void eject_card() const { std::cout << "Ejecting card\n"; }
};

} // namespace atm
