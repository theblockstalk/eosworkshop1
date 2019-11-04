#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace std;
using namespace eosio;

CONTRACT spendingctrl : public contract {
  public:
    using contract::contract;

    ACTION clear();

  private:
    TABLE balance {
      name    user;
      asset   balance;
      auto primary_key() const { return user.value; }
    };
    typedef multi_index<name("messages"), balance> balance_table;
};
