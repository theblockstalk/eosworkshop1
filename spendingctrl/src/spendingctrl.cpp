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

ACTION spendingctrl::withdrawal(name user, asset quantity, std::string memo) {
  auto self = get_self();

  balance_table _balances(self, self.value);

  auto itr = _balances.find(user.value);
  check(itr != _balances.end(), "No account for user in this wallet");
  check(itr->balance.amount > 0, "User does not have sufficient funds");

  auto ram_payer = user;
  _balances.modify(itr, ram_payer, [&](auto& row) {
    row.balance -= quantity;
  });

  token::transfer_action eosio_token_transfer(name("eosio.token"), {self, "active"_n});
  eosio_token_transfer.send(self, user, quantity, memo);
}

ACTION spendingctrl::clear() {
  require_auth(get_self());

  balance_table _balances(get_self(), get_self().value);

  auto msg_itr = _balances.begin();
  while (msg_itr != _balances.end()) {
    msg_itr = _balances.erase(msg_itr);
  }
}
