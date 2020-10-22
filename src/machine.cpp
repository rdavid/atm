#include "machine.hpp"
#include "driver.hpp"
#include <map>
#include <string>

namespace atm {

// States definitions.
class c_state {
 public:
  virtual std::string get_id() const = 0;
  virtual const c_state* handle(const c_event&, driver&) const = 0;
  static const c_state* get_state(const std::string& id) {
    std::map<std::string, const c_state*>::const_iterator it =
      s_db.find(id);
    return it != s_db.end() ? it->second : NULL;
  }
 protected:
  c_state() {}
  virtual ~c_state() {}
  void add(const std::string& id) {
    s_db.insert(std::make_pair(id, this));
  }
 private:
  c_state(const c_state&);
  c_state& operator=(const c_state&);
  static std::map<std::string, const c_state*> s_db;
};

// Static. Private.
std::map<std::string, const c_state*> c_state::s_db;

class c_state_init : public c_state {
 public:
  c_state_init() { add(get_id()); }
  virtual std::string get_id() const { return "init"; }
  virtual const c_state* handle(const c_event& e, driver& d) const {
    if (e.get_id() != "insert") {
      d.m_interface.get().display_enter_card();
      return this;
    }
    d.m_interface.get().display_enter_pin();
    return get_state("card_in");
  }
 private:
  static c_state_init s_inst;
};

// Static. Private.
c_state_init c_state_init::s_inst;

class c_state_card_in : public c_state {
 public:
  c_state_card_in() { add(get_id()); }
  virtual std::string get_id() const { return "card_in"; }
  virtual const c_state* handle(const c_event& e, driver& d) const {
    if (e.get_id() != "digit" || d.m_pass.str().length() > 4) {
      d.m_pass.str("");
      d.m_account.clear();
      d.m_interface.get().eject_card();
      d.m_interface.get().display_enter_card();
      return get_state("init");
    }
    if (d.m_pass.str().length() < 4) {
      return this;
    }
    if (d.m_bank.get().verify_pin(d.m_account, d.m_pass.str())) {
      d.
      m_interface.
      get().
      display_withdrawal_options();
      return get_state("pin_ok");
    }
    d.m_pass.str("");
    d.m_account.clear();
    d.m_interface.get().display_pin_incorrect_message();
    d.m_interface.get().eject_card();
    d.m_interface.get().display_enter_card();
    return get_state("init");
  }
 private:
  static c_state_card_in s_inst;
};

// Static. Private.
c_state_card_in c_state_card_in::s_inst;

class c_state_pin_ok : public c_state {
 public:
  c_state_pin_ok() { add(get_id()); }
  virtual std::string get_id() const { return "pin_ok"; }
  virtual const c_state* handle(const c_event& e, driver& d) const {
    if (e.get_id() == "withdraw") {
      d.m_bank.get().withdraw(d.m_account, d.m_amount);
      d.m_interface.get().issue_money(d.m_amount);
      return this;
    }
    if (e.get_id() == "balance") {
      auto b = d.m_bank.get().balance(d.m_account);
      d.m_interface.get().display_balance(b);
      return this;
    }
    std::cerr << "Event " << e.get_id() << " is not handled." << std::endl;
    return this;
  }
 private:
  static c_state_pin_ok s_inst;
};

// Static. Private.
c_state_pin_ok c_state_pin_ok::s_inst;

// State machine definition.
c_machine::c_machine(): m_state (c_state::get_state("init"))
{}

void c_machine::handle(const c_event& e, driver& d) {
  m_state = m_state->handle(e, d);
}

void c_machine::reset() {
  m_state = c_state::get_state("init");
}

}  // namespace atm
