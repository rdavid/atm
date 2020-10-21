Implement a simple ATM system.

The system should include 3 components:

- [User interface](include/interface_handler.hpp).
- [ATM logic](include/atm_handler.hpp).
- [Bank communication](include/bank_handler.hpp).

For maximizing responsiveness communication between these components should be non-blocking, so, for example the `atm_handler` can't call a function of `user_interface` directly because it would block it from handling other events.

At start, the system should wait for a card to be inserted. Once the card is inserted, it then waits for the user to enter their PIN, one digit at a time. Once enough digits have been entered, the PIN is verified. If the PIN is not OK, you’re finished, so you return the card to the customer and resume waiting for someone to enter their card. If the PIN is OK, you wait for them to either cancel the transaction, display their balance or withdraw 50. If they cancel, you’re finished, and you return their card. If they select to withdraw, you wait for confirmation from the bank before issuing the cash and returning the card or displaying an “insufficient funds” message and returning their card.

Every user operation other than the above should be ignored.

Assume a legal PIN is of 4 digit length.

Your code should interact with the user and bank using the interfaces in [`interface.hpp`](include/interface.hpp) and [`bank.hpp`](include/bank.hpp). 

[`main.cpp`](src/main.hpp) will be used to drive the application.

Run example:

```bash
Please enter your card (i)
i
Please enter your PIN (0-9)
3412
PIN incorrect
Ejecting card
Please enter your card (i)
i
Please enter your PIN (0-9)
1234
Withdraw 50? (w)
Display Balance? (b)
Cancel? (c)
w
Issuing 50
b
The balance of your account is 50
c
Cancelled
Ejecting card
Please enter your card (i)
i
Please enter your PIN (0-9)
1234
Withdraw 50? (w)
Display Balance? (b)
Cancel? (c)
b
The balance of your account is 50
q
```

- You should implement the functions in [`driver.cpp`](src/driver.cpp).
- You are provided with CMake build scripts but allowed to use any build system you wish.
- Free free to add member variables and functions to the above classes as you see fit as well as defining additional types.
- Your solution should compile and run without errors.
- For bonus points, add unit tests to check your implementation.
