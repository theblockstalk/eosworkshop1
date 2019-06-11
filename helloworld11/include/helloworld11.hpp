#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

CONTRACT helloworld11 : public contract {
  public:
    // Table definition
    TABLE message_struct {
      name user;
      std::string msg;
      
      auto primary_key() const { return user.value; }
      EOSLIB_SERIALIZE(message_struct, (user)(msg))
    };
    typedef eosio::multi_index<"messages"_n, message_struct> messages;
    
    // Constructor
    helloworld11(eosio::name receiver, eosio::name code, datastream<const char*> ds) :
      contract(receiver, code, ds), // constructure of eosio::contract
      messages_tb(_self, _self.value) {}// table constructor eosio::multi_index<tablename, struct> tablename(code, scope)

    // Public actions
    ACTION hi(name user);
    
    ACTION setmsg(name user, std::string msg);
  
  private:
    // Storage table variables
    messages messages_tb;
};

EOSIO_DISPATCH(helloworld11, (hi)(setmsg))
