#include <spendingctrl.hpp>

void spendingctrl::withdrawal(const name user, const asset quantity, string& memo) {
  require_auth( user );
  print("\n wallet withdrawal");
  
  auto self = get_self();

  auto sym = quantity.symbol.code();
  users_table users(self, sym.raw());
    
  auto itr = users.find(user.value);
  
  if ( itr != users.end()) {
    asset limit = itr->limit;
    // TODO: if (limit exists ) {
          print("\n this user has a withdrawal limit of ", limit.to_string());
      eosio::check(limit.amount >= quantity.amount, "cannot withdraw more than limit");
    // }

    time_point_sec last_withdrawal = itr->last_withdrawal;
    // TODO: if ( last_withdrawal exists ) {
      eosio::check(last_withdrawal < time_point_sec(current_time_point() - hours(24)), "cannot withdraw more than once per 24 hours");
    // }

    asset balance = itr->balance;
    eosio::check(balance.amount >= quantity.amount, "cannot withdraw more than balance");
    
    auto ram_payer = user;
    users.modify(itr, ram_payer, [&](auto& row) {
      row.last_withdrawal = current_time_point();
    });
  }
  
  // spendingctrl needs to have active permission of spendingctrl@eosio.code
  action(
    permission_level{get_self(), "active"_n}, // permission
    "eosio.token"_n, // account to send action to "code"
    "transfer"_n, // action
    std::make_tuple(self, user, quantity, memo) // data
  ).send();
}

void spendingctrl::ontransfer(const name from, const name to, const asset quantity, string& memo) {
  print("notification = transfer( from: ", from.to_string(), ", to: ", to.to_string(), ", quantity: ", quantity.to_string(), ", memo: ", memo, " )");
  
  auto self = get_self();
  
  if (to == self) {
    print("\n wallet deposit");
    
    auto sym = quantity.symbol.code();
    users_table users(self, sym.raw());
    
    auto ram_payer = to;
    
    auto itr = users.find(to.value);
    
    if ( itr == users.end()) {
      users.emplace(ram_payer, [&](auto& row) {
        row.user = to;
        row.balance = quantity;
      });
    } else {
      users.modify(itr, ram_payer, [&](auto& row) {
        row.balance += quantity;
      });
    }
  } else if (from == self) {
    print("\n wallet withdrawal");
    // never triggered as require_recipient( from ) will not send notification when auth is from account from
    
    // user withdrawal() instead
  }
}

    
void spendingctrl::setdaylimit(name user, asset limit) {
  
  require_auth(user);
  
  limit.is_valid();

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






