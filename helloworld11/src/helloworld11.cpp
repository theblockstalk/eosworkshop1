#include <helloworld11.hpp>

ACTION helloworld11::hi(name from, const checksum256 &message_hash) {
  require_auth(from);

  // Init the _message table
  messages_table _messages(get_self(), get_self().value);
  time_point last_updated = current_time_point();

  // Find the record from _messages table
  auto msg_itr = _messages.find(from.value);
  if (msg_itr == _messages.end()) {
    // Create a message record if it does not exist
    _messages.emplace(from, [&](auto& msg) {
      msg.user = from;
      msg.hash = message_hash;
      msg.last_updated = last_updated;
    });
  } else {
    // Modify a message record if it exists
    _messages.modify(msg_itr, from, [&](auto& msg) {
      msg.hash = message_hash;
      msg.last_updated = last_updated;
    });
  }
}

ACTION helloworld11::hiverify(name from, string message) {
  // Init the _message table
  messages_table _messages(get_self(), get_self().value);

  // Find the record from _messages table
  auto msg_itr = _messages.find(from.value);
  if (msg_itr != _messages.end()) {
    checksum256 hash = msg_itr->hash;
    assert_sha256(
      message.c_str(),
      strlen(message.c_str()),
      hash
    );
    msg_itr = _messages.erase(msg_itr);
  }
}

ACTION helloworld11::clear() {
  require_auth(get_self());

  messages_table _messages(get_self(), get_self().value);

  // Delete all records in _messages table
  auto msg_itr = _messages.begin();
  while (msg_itr != _messages.end()) {
    msg_itr = _messages.erase(msg_itr);
  }
}

EOSIO_DISPATCH(helloworld11, (hi)(hiverify)(clear))
