#include <spendingctrl.hpp>

void spendingctrl::transfer(const name from, const name to, const asset quantity, string& memo) {
  print("notification = transfer( from: ", from.to_string(), ", to: ", to.to_string(), ", quantity: ", quantity.to_string(), ", memo: ", memo, " )");
  
  auto self = get_self();

  auto sym = quantity.symbol.code();
  users_table users(self, sym.raw());
    
  if (from == self) {
    print("\n wallet withdrawal");

    auto itr = users.find(to.value);
    
    if ( itr != users.end()) {
      asset limit = itr->limit;
      print("\n this token has a withdrawal limit of ", limit.to_string());
      
      eosio::check(limit.amount >= quantity.amount, "cannot withdraw more than limit");
      eosio::check(itr->last_withdrawal < time_point_sec(current_time_point() - hours(24)), "cannot withdraw more than once per 24 hours");
      
      auto ram_payer = to;
      users.modify(itr, ram_payer, [&](auto& row) {
        row.last_withdrawal = current_time_point();
      });
    } else {
      print("\n no withdrawal limit for this asset");
    }
  } else if (to == self) {
    print("\n wallet deposit");
  }
}



    
void spendingctrl::setdaylimit(name user, asset limit) {
  
  require_auth(user);
  
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
      // row.last_withdrawal = time_point_sec(current_time_point() + hours(24));
    });
  }
}











