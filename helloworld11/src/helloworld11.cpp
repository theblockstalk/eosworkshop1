#include <helloworld11.hpp>

ACTION helloworld11::hi(name user) {
  require_auth(user);
  print("Hello, ", name{user});

  const auto msgItr = customMessages.find(user.value);
  if ( msgItr != customMessages.end() ) {
    print("\n", msgItr->name);
  }
}

ACTION helloworld11::setmessage(name key, std::string message) {
  require_auth(key);

  const auto msgItr = customMessages.find(key.value);
  if ( msgItr == customMessages.end() ) {
    // Create a new table row
    customMessages.emplace(_self, [&](tableStruct &t) {
      t.key = key;
      t.name = message;
    });
  } else {
    // Modify a table row
    customMessages.modify(msgItr, _self, [&](tableStruct &t) {
      t.name = message;
    });
  }
}
