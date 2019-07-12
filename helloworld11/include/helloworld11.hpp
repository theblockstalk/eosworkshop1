#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

CONTRACT helloworld11 : public contract {
  public:
    using contract::contract;
    helloworld11(eosio::name receiver, eosio::name code, datastream<const char*> ds):
    contract(receiver, code, ds),
    customMessages(_self, _self.value) {} // initializes the variable

    ACTION hi(name user);

    ACTION setmessage(name key, std::string message);

  private:
    TABLE tableStruct {
      name key;
      std::string name;

      auto primary_key() const { return key.value; }
    };
    typedef eosio::multi_index<"table"_n, tableStruct> table;

    table customMessages;
};

EOSIO_DISPATCH(helloworld11, (hi)(setmessage)) // this can be deleted
