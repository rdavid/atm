// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#pragma once

#include <cassert>
#include <string>

namespace atm
{
class bank
{
public:
  bool verify_pin([[maybe_unused]] const std::string& account, const std::string& PIN) const
  {
    assert(account == "test_account");
    return PIN == "1234";
  }

  void withdraw([[maybe_unused]] const std::string& account, unsigned amount)
  {
    assert(account == "test_account");
    m_balance -= amount;
  }

  unsigned balance([[maybe_unused]] const std::string& account) const
  {
    assert(account == "test_account");
    return m_balance;
  }

private:
  unsigned m_balance = 100;
};

} // namespace atm
