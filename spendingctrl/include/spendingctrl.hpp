#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/asset.hpp>
#include <eosio/name.hpp>
#include <eosio/system.hpp> // needed for current_time_point()

#include <string>

using namespace eosio;
using namespace std;

CONTRACT spendingctrl : public contract {
  public:
    using contract::contract;
    
    spendingctrl(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}
    
    // Set limits
    ACTION setdaylimit(name user, asset limit);

    // Withdrawals  
    ACTION withdrawal(const name user, const asset quantity, string& memo);
    
    // Deposits
    [[eosio::on_notify("eosio.token::transfer")]] void ontransfer(const name from, const name to, const asset quantity, string& memo);
    
    // A handy function while testing and developing a contract
    // Removes all table data, in case structure changes.
    // Should not exist in final contract
    ACTION clear(name user);

  private:
  
    TABLE user {
      name user;
      asset limit;
      asset balance;
      time_point_sec last_withdrawal;
      
      uint64_t primary_key() const { return user.value; }
    };

    typedef multi_index< "users"_n, user> users_table;
    
};