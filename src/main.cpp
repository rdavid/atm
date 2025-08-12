// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#include <cstdio>
#include <driver.hpp>
#include <iostream>
#include <string>

int main()
{
  atm::driver driver;
  bool quit_pressed = false;
  while (!quit_pressed) {
    switch (auto c = static_cast<char>(std::getchar()); c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      driver.digit_pressed(c);
      break;
    case 'b':
      driver.balance_pressed();
      break;
    case 'w':
      driver.withdraw_pressed(50);
      break;
    case 'c':
      driver.cancel_pressed();
      break;
    case 'q':
      quit_pressed = true;
      break;
    case 'i':
      driver.card_inserted("test_account");
      break;
    }
  }
}
