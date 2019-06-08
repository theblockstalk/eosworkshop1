Spending control
================

Alice sends 1000 TOKEN to the contract CTR.

CTR registers Alice's balance.

Alice executes `CTR->dailylimit()` to set the daily spending limit to 10
TOKEN.

Alice executes `CTR->pay(Bob, "1.0000 TOKEN")`, and CTR transfers the
token from Alice's balance to Bob.

Alice sets up an additional permission with a new private key that is
only allowed to pay through CTR.

If Alice tries to spend more than the daily limit, she gets an
exception.

If Alice tries to spend more than there is token on the balance, she gets an exception.

CTR should accept any token for deposits and spending, even if multiple
token contracts use the same symbol.

*Extra excercise*: CTR defines a loan interest for certain known
 tokens. If Alice overspends her balalce, next time she deposits, CTR
 deducts the debt and the interest.


Attacks to watch out: check that to=self on incoming transfer. Always
check the contract name of the token.









