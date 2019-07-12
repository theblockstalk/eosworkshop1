#include <spendingctrl.hpp>

void spendingctrl::transfer(const name from, const name to, const asset quantity, string& memo) {
  print("notification = transfer( from: ", from.to_string(), ", to: ", to.to_string(), ", quantity: ", quantity.to_string(), ", memo: ", memo, " )");
  
  auto self = get_self();

  auto sym = quantity.symbol.code();
  users_table users(self, sym.raw());
    
  // if (from == self) {
  //   print("\n wallet withdrawal");
  //   // TODO: throw error. you cannot transfer out of this contract without the withdraw function
    
  //   // limit transfer to limit. if not throw error...
  //   // check transfer not done in < 24 hours
  //   // check amount < limit
  //   // check amount < balance .... do we even need to track balance???
  //   // transfer...
    
  //   // do nothing (allow transfer to occure)
  // } else if (to == self) {
  //   print("\n wallet deposit");
  //   auto itr = users.find(to.value);
    
  //   auto ram_payer = to;
  //   if ( itr != users.end() ) {
  //     users.modify(itr, ram_payer, [&](auto& row) {
  //       // row.balance += quantity;
  //     });
  //   } else {
  //     users.emplace(ram_payer, [&](auto& row) {
  //       row.user = to;
  //       // row.balance = quantity;
  //     });
  //   }
  // }
}



    
void spendingctrl::setdaylimit(name user, asset limit) {
  
  require_auth(user);
  
  auto self = get_self();
  auto ram_payer = user;
  
  auto sym = limit.symbol.code();
  users_table users(self, sym.raw());
  
  auto itr = users.find(user.value);
  
  if(itr != users.end()){
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











