#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT helloworld11 : public contract {
  public:
    using contract::contract;

    ACTION hi(name from, string message, uint64_t plus_x);
    ACTION clear();

  private:
    TABLE messages {
      name    user;
      string  text;
      uint64_t x;
      auto primary_key() const { return user.value; }
    };
    typedef multi_index<name("messages"), messages> messages_table;
};
