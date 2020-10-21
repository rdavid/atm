#include <driver.hpp>

namespace atm
{

// https://bugs.llvm.org/show_bug.cgi?id=23728
// clang-format off

void driver::digit_pressed(char /* digit */) { /* PUT YOUR CODE HERE */ }

void driver::balance_pressed() { /* PUT YOUR CODE HERE */ }

void driver::withdraw_pressed(unsigned /* amount */) { /* PUT YOUR CODE HERE */ }

void driver::card_inserted(const std::string& /* account */) { /* PUT YOUR CODE HERE */ }

void driver::cancel_pressed() { /* PUT YOUR CODE HERE */ }

// clang-format on

} // namespace atm
