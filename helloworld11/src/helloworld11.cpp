#include <helloworld11.hpp>

ACTION helloworld11::hi(name user) {
  require_auth(user);
  
  print("Hello, ", name{user});
  
  const auto msgItr = messages_tb.find(user.value);
  if ( msgItr != messages_tb.end() ) {
    print("\n", msgItr->msg);
  }
}


ACTION helloworld11::setmsg(name user, std::string msg) {
  require_auth(user);
  
  const auto msgItr = messages_tb.find(user.value);
  if ( msgItr == messages_tb.end() ) {
    // Create a new table row
    messages_tb.emplace(_self, [&](message_struct &m) {
      m.user = user;
      m.msg = msg;
    });
  } else {
    // Modify a table row
    messages_tb.modify(msgItr, _self, [&](message_struct &m) {
      m.user = user;
      m.msg = msg;
    });
  }
}