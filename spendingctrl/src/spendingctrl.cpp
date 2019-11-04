#include <spendingctrl.hpp>

ACTION spendingctrl::clear() {
  require_auth(get_self());

  balance_table _balances(get_self(), get_self().value);

  // Delete all records in _messages table
  auto msg_itr = _balances.begin();
  while (msg_itr != _balances.end()) {
    msg_itr = _balances.erase(msg_itr);
  }
}
