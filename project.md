Spending control
================

Alice sends 1000 TOKEN to the contract CTR.

CTR registers Alice's balance. The contract verifies that this is a
particular token on a known token contract.

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

* Let the users register themselves first at CTR, and only then accept
  payments from them.

* Extend CTR to accept any token for deposits and spending, even if
  multiple token contracts use the same symbol.


* Alice executes `CTR->dailylimit()` to set the daily spending limit. If
  Alice tries to spend more than the daily limit, she gets an exception.


* CTR defines a loan interest for certain known tokens. If Alice
  overspends her balalce, next time she deposits, CTR deducts the debt
  and the interest.


* CTR issues receipts as inline actions with notifications to Alice,
  indicating each payment details and remaining balance.
  


