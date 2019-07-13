#include <spendingctrl.hpp>

void spendingctrl::withdrawal(const name user, const asset quantity, string& memo) {
  require_auth( user );
  
  auto self = get_self();

  auto sym = quantity.symbol.code();
  users_table users(self, sym.raw());
    
    auto itr = users.find(user.value);
    
    if ( itr != users.end()) {
      asset limit = itr->limit;
      print("\n this token has a withdrawal limit of ", limit.to_string());
      
      eosio::check(limit.amount >= quantity.amount, "cannot withdraw more than limit");
      eosio::check(itr->last_withdrawal < time_point_sec(current_time_point() - hours(24)), "cannot withdraw more than once per 24 hours");
      
      auto ram_payer = user;
      users.modify(itr, ram_payer, [&](auto& row) {
        row.last_withdrawal = current_time_point();
      });
      
      action(
        permission_level{get_self(), "active"_n}, // permission
        "eosio.token"_n, // account "code"
        "transfer"_n, // action
        std::make_tuple(self, user, quantity, memo) // data
      ).send();
    }
}

void spendingctrl::ontransfer(const name from, const name to, const asset quantity, string& memo) {
  print("notification = transfer( from: ", from.to_string(), ", to: ", to.to_string(), ", quantity: ", quantity.to_string(), ", memo: ", memo, " )");
  
  auto self = get_self();
  
  if (to == self) {
    print("\n wallet deposit");
  } else if (from == self) {
    // never triggered as require_recipient( from ) will not send notification when auth is from account from
  }
}

    
void spendingctrl::setdaylimit(name user, asset limit) {
  
  require_auth(user);
  
  limit.is_valid();
  // eosio::check(limit.symbol == symbol("EOS", 4), "must be EOS token");

  auto self = get_self();
  auto ram_payer = user;
  
  auto sym = limit.symbol.code();
  users_table users(self, sym.raw());
  
  auto itr = users.find(user.value);
  
  if(itr == users.end()){
    users.emplace(user, [&](auto& row){
      row.user = user;
      row.limit = limit;
    });
  } else {
    users.modify(itr, user, [&](auto& row){
      row.limit = limit;
    });
  }
}



void spendingctrl::clear(name user) {
  auto self = get_self();
  
  require_auth(self);
  users_table users(self, user.value);
  
  auto itr = users.begin();
  while (itr != users.end()) {
    itr = users.erase(itr);
  }
}






