#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/asset.hpp>
#include <eosio/name.hpp>
// #include <eosio/singleton.hpp>

#include <string>

using namespace eosio;
using namespace std;

CONTRACT spendingctrl : public contract {
  public:
    using contract::contract;
    
    spendingctrl(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}
    
    ACTION setdaylimit(name user, asset limit);
    
    [[eosio::on_notify("eosio.token::transfer")]]
    void transfer(const name from, const name to, const asset quantity, string& memo);
    
  private:
  
    TABLE user {
      name      user;
      // asset     balance;
      asset     limit;
      time_point_sec  last_withdrawal;
      
      uint64_t primary_key() const { return user.value; }
    };

    typedef multi_index< "users"_n, user> users_table;
    
};