#include <driver.hpp>

namespace atm
{

// https://bugs.llvm.org/show_bug.cgi?id=23728
// clang-format off

driver::driver() {
  m_interface.get().display_enter_card();
}

void driver::digit_pressed(char digit) {
  if (m_account.empty()) {
    m_interface.get().display_enter_card();
    return;
  }
  m_pass << digit;
  if (m_pass.str().length() < 4) {
    return;
  }
  std::cout << "Pass is " << m_pass.str() << std::endl;
  m_pass.flush();
}

void driver::balance_pressed() { /* PUT YOUR CODE HERE */ }

void driver::withdraw_pressed(unsigned /* amount */) { /* PUT YOUR CODE HERE */ }

void driver::card_inserted(const std::string& account) {
  m_account = account;
  m_interface.get().display_enter_pin();
}

void driver::cancel_pressed() {
  m_account.clear();
  m_pass.flush();
}

// clang-format on

} // namespace atm
