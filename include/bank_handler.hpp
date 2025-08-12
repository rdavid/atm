// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#pragma once

#include <bank.hpp>
#include <future>

namespace atm
{

class bank_handler {
 public:
  std::future<bool> verify_pin(const std::string& account,
                               const std::string& pin) const {
    return std::async(&bank::verify_pin, &m_bank, account, pin);
  }
  std::future<void> withdraw(const std::string& account, unsigned amount) {
    return std::async(&bank::withdraw, &m_bank, account, amount);
  }
  std::future<unsigned> balance(const std::string& account) const {
    return std::async(&bank::balance, &m_bank, account);
  }
 private:
  bank m_bank;
};

}  // namespace atm
