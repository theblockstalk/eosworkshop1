

Fidelity token
==============

A shop issues their own token FIDL as fidelity bonus to its customers.
The customer can spend FIDL to get discounts at the shop and some
neighbor businesses.

Some customers do not have an eosio account.

The shop keeps track of each customer by giving them unique 64bit
customer ID.

Alice spends $100 in the shop. The shopkeeper knows her customer ID.

The shopkeeper asks Alice if she has an eosio account. 

If she does not, a contract CTR keeps track of FIDL balances for each
customer ID. The shopkeeper issues 100 FIDL to CTR and CTR updates
Alice's balance.

If she does, the shopkeeper issues FIDL to her account.

If this is the first time Alice has got an account, CTR transfers
Alice's balance to her account.

CTR keeps the link to Alice's account, and the shopkeeper does not need
to ask next time.


















