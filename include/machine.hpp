// SPDX-FileCopyrightText: 2020-2026 David Rabkin
// SPDX-License-Identifier: 0BSD
#pragma once
#include <string>

namespace atm {

class driver;
class c_state;

// c_events definitions.
struct c_event {
  c_event() = default;
  c_event(const c_event&) = delete;
  c_event& operator=(const c_event&) = delete;
  c_event(c_event&&) = delete;
  c_event& operator=(c_event&&) = delete;
  virtual ~c_event() = default;
  virtual std::string get_id() const = 0;
};

struct c_event_insert : c_event {
  std::string get_id() const override { return "insert"; }
};

struct c_event_digit : c_event {
  std::string get_id() const override { return "digit"; }
};

struct c_event_balance : c_event {
  std::string get_id() const override { return "balance"; }
};

struct c_event_withdraw : c_event {
  std::string get_id() const override { return "withdraw"; }
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
