// SPDX-FileCopyrightText: 2020-2025 David Rabkin
// SPDX-License-Identifier: 0BSD
#pragma once
#include <string>

namespace atm {

class driver;
class c_state;

// c_events definitions.
struct c_event {
  virtual ~c_event() {};
  virtual std::string get_id() const = 0;
};

struct c_event_insert : c_event {
  virtual std::string get_id() const { return "insert"; }
};

struct c_event_digit : c_event {
  virtual std::string get_id() const { return "digit"; }
};

struct c_event_balance : c_event {
  virtual std::string get_id() const { return "balance"; }
};

struct c_event_withdraw : c_event {
  virtual std::string get_id() const { return "withdraw"; }
};

// State machine.
class c_machine {
 public:
  c_machine();
  void handle(const c_event& e, driver& d);
  void reset();
 private:
  const c_state* m_state;
};

}  // namespace atm
