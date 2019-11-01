#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

using namespace std;
using namespace eosio;

CONTRACT helloworld11 : public contract {
  public:
    using contract::contract;

    ACTION hi(name from, string message);
    ACTION clear();

  private:
    TABLE messages {
      name    user;
      string  text;
      time_point last_updated;
      auto primary_key() const { return user.value; }
    };
    typedef multi_index<name("messages"), messages> messages_table;
};
