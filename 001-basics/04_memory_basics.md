# Memory and References in C++

Welcome to your third C++ tutorial! Here you'll learn how C++ manages memory and how to use references efficiently.

## Learning Objectives
- Understand how computer memory works
- Learn about variables in memory
- Master references and their uses
- Practice memory safety (crucial for Bitcoin development)

## What is Computer Memory?

Think of computer memory like a huge set of numbered boxes:
```cpp
int number = 42;    // The value 42 is stored in a memory "box"
```

### Memory Visualization
```
Memory Box:
+--------+
|   42   | <- number
+--------+
```

## Stack Memory (Simple Storage)

The stack is like a stack of boxes - simple and automatic:

```cpp
int main() {
    int blockHeight = 750000;     // Goes on the stack
    double btcPrice = 45000.00;   // Also on the stack
    bool isValid = true;          // Stack as well
    
    // All variables above are automatically cleaned up
    return 0;
}
```

### Practice Program: Stack Variables
```cpp
#include <iostream>

int main() {
    // Create some stack variables
    int transactionCount = 5;
    double totalAmount = 1.5;     // 1.5 BTC
    
    // Show memory usage
    std::cout << "Transaction count is stored in memory\n";
    std::cout << "Value: " << transactionCount << std::endl;
    std::cout << "Size: " << sizeof(transactionCount) << " bytes\n";
    
    return 0;
}
```

## References (Memory Aliases)

A reference is like a nickname for a memory location:

```cpp
int bitcoinAmount = 5;          // Original variable
int& amountRef = bitcoinAmount; // Reference to bitcoinAmount

amountRef = 10;                 // Changes bitcoinAmount too!
std::cout << bitcoinAmount;     // Prints 10
```

### Practice Program: References
```cpp
#include <iostream>

void updateBalance(double& balance, double amount) {
    balance += amount;  // Modifies original balance
}

int main() {
    double walletBalance = 1.0;  // 1 BTC
    
    std::cout << "Initial balance: " << walletBalance << " BTC\n";
    
    updateBalance(walletBalance, 0.5);  // Add 0.5 BTC
    std::cout << "New balance: " << walletBalance << " BTC\n";
    
    return 0;
}
```

## Const References (Safe Sharing)

Use const references to safely share memory without copying:

```cpp
void displayTransaction(const double& amount) {
    // Can read amount but can't modify it
    std::cout << "Amount: " << amount << " BTC\n";
}
```

### Practice Program: Const References
```cpp
#include <iostream>

void verifyAmount(const double& amount) {
    if (amount > 0 && amount <= 21000000) {
        std::cout << "Valid amount: " << amount << " BTC\n";
    } else {
        std::cout << "Invalid amount!\n";
    }
}

int main() {
    double payment = 0.5;  // 0.5 BTC
    verifyAmount(payment); // Safely shares payment
    return 0;
}
```

## Memory Safety Examples

### 1. Safe Reference Usage
```cpp
int main() {
    // Good: Reference has a valid target
    double amount = 1.0;
    double& amountRef = amount;
    
    // Bad: Never do this!
    // double& badRef;  // Error: references must be initialized
    
    return 0;
}
```

### 2. Const Correctness
```cpp
void processPayment(const double& amount) {
    // amount cannot be modified here
    std::cout << "Processing " << amount << " BTC\n";
}

int main() {
    double payment = 0.1;
    processPayment(payment);  // payment is safely shared
    return 0;
}
```

## Practice Exercises

### 1. Wallet Balance Manager
```cpp
#include <iostream>

void addToBalance(double& balance, double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

void subtractFromBalance(double& balance, double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
    }
}

int main() {
    double walletBalance = 1.0;
    
    addToBalance(walletBalance, 0.5);
    std::cout << "After deposit: " << walletBalance << " BTC\n";
    
    subtractFromBalance(walletBalance, 0.3);
    std::cout << "After withdrawal: " << walletBalance << " BTC\n";
    
    return 0;
}
```

### 2. Transaction Validator
```cpp
#include <iostream>

bool validateTransaction(const double& amount, const double& balance) {
    return amount > 0 && amount <= balance;
}

int main() {
    double accountBalance = 2.0;
    double paymentAmount = 1.5;
    
    if (validateTransaction(paymentAmount, accountBalance)) {
        std::cout << "Transaction valid!\n";
    } else {
        std::cout << "Transaction invalid!\n";
    }
    
    return 0;
}
```

## Common Mistakes to Avoid

### 1. Dangling References
```cpp
// NEVER DO THIS:
int& getDanglingReference() {
    int value = 42;
    return value;  // WRONG: returning reference to local variable
}

// DO THIS INSTEAD:
int getValueSafely() {
    int value = 42;
    return value;  // Returns a copy - safe!
}
```

### 2. Null References
```cpp
// References cannot be null
double& ref = *nullptr;  // NEVER do this!

// Use pointers if you need null values
double* ptr = nullptr;   // This is okay for pointers
```

## Knowledge Check

Try to answer these questions:
1. What's the difference between stack and heap memory?
2. Why use references instead of copying values?
3. When should you use const references?
4. Can a reference be null?
5. Why is memory safety important in Bitcoin applications?

## Bitcoin-Specific Memory Tips

1. Always validate transaction amounts before modifying balances
2. Use const references when sharing sensitive financial data
3. Be extra careful with memory when handling private keys
4. Verify all inputs before committing to memory changes

## Next Steps

1. **Experiment!** Try:
   - Creating different types of references
   - Using const references in functions
   - Building a simple balance tracker

2. **Challenge Yourself:**
   - Create a transaction history system
   - Implement a multi-wallet balance manager
   - Add input validation to all exercises

3. When you're comfortable with memory and references, move on to [Functions and Error Handling](04_functions.md)

Remember:
- Always initialize references
- Use const when possible
- Think about memory safety
- Practice with realistic examples