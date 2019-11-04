#include <spendingctrl.hpp>

[[eosio::on_notify("eosio.token::transfer")]] void spendingctrl::deposit(name from, name to,  asset quantity, std::string memo) {
  auto self = get_self();

  if (to == self) {
    balance_table _balances(self, self.value);

    auto ram_payer = to;

    auto itr = _balances.find(from.value);
    if ( itr == _balances.end()) {
      _balances.emplace(ram_payer, [&](auto& row) {
        row.user = from;
        row.balance = quantity;
      });
    } else {
      _balances.modify(itr, ram_payer, [&](auto& row) {
        row.balance += quantity;
      });
    }
  }
}

ACTION spendingctrl::clear() {
  require_auth(get_self());

  balance_table _balances(get_self(), get_self().value);

  // Delete all records in _messages table
  auto msg_itr = _balances.begin();
  while (msg_itr != _balances.end()) {
    msg_itr = _balances.erase(msg_itr);
  }
}
