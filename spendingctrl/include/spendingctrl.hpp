#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/system.hpp>
#include "eosio.token.hpp"

using namespace std;
using namespace eosio;

CONTRACT spendingctrl : public contract {
  public:
    using contract::contract;

    [[eosio::on_notify("eosio.token::transfer")]] void deposit(name from, name to,  asset quantity, std::string memo);

    ACTION withdrawal(name user, asset quantity, std::string memo);

    ACTION setdaylimit(name user, asset limit);

    ACTION clear();

  private:
    TABLE balance {
      name    user;
      asset   balance;
      asset   limit;
      time_point last_withdrawal;
      auto primary_key() const { return user.value; }
    };
    typedef multi_index<name("balance"), balance> balance_table;
};
