Spending control
================

Alice sends 1000 TOKEN to the contract CTR.

CTR registers Alice's balance. The contract verifies that this is a
particlar token on a known token contract.

Alice executes `CTR->pay(Bob, "1.0000 TOKEN", memo)`, and CTR transfers the
token from Alice's balance to Bob.

Alice sets up an additional permission with a new private key that is
only allowed to pay through CTR.

If Alice tries to spend more than there is token on the balance, she
gets an exception.

Attacks to watch out: check that to=self on incoming transfer. Always
check the contract name of the token.


Extra excercises
----------------

* Extend CTR to accept any token for deposits and spending, even if
  multiple token contracts use the same symbol.


* Alice executes `CTR->dailylimit()` to set the daily spending limit. If
  Alice tries to spend more than the daily limit, she gets an exception.


* CTR defines a loan interest for certain known tokens. If Alice
  overspends her balalce, next time she deposits, CTR deducts the debt
  and the interest.


* CTR issues receipts as inline actions with notifications to Alice,
  indicating each payment details and remaining balance.
  



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


















