# Functions and Error Handling in C++

Welcome to your fourth C++ tutorial! Here you'll learn how to create reusable blocks of code and handle errors safely.

## Learning Objectives
- Understand what functions are and why we use them
- Learn to create and use functions
- Master error handling techniques
- Practice with Bitcoin-relevant examples

## What is a Function?

A function is like a recipe - it takes ingredients (parameters) and produces a result:
```cpp
// Simple function that adds two numbers
int add(int a, int b) {
    return a + b;
}

// Using the function
int result = add(5, 3);  // result = 8
```

## Basic Function Structure

### Parts of a Function
```cpp
// Return type | Name | Parameters
   int         sum    (int x, int y) {
       // Function body
       return x + y;   // Return statement
   }
```

### Practice Program: Simple Calculator
```cpp
#include <iostream>

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

int main() {
    double num1 = 10.5;
    double num2 = 5.25;
    
    std::cout << num1 << " + " << num2 << " = " << add(num1, num2) << std::endl;
    std::cout << num1 << " - " << num2 << " = " << subtract(num1, num2) << std::endl;
    
    return 0;
}
```

## Functions with Bitcoin Examples

### 1. Basic Transaction Validation
```cpp
bool isValidAmount(double amount) {
    // Bitcoin amounts must be positive and not exceed total supply
    return amount > 0 && amount <= 21000000;
}

// Usage
double payment = 0.5;  // 0.5 BTC
if (isValidAmount(payment)) {
    std::cout << "Valid payment amount\n";
}
```

### 2. Fee Calculator
```cpp
double calculateFee(double amount, double feeRate) {
    if (amount <= 0) {
        return 0;  // Invalid amount
    }
    return amount * feeRate;
}

// Usage
double transaction = 1.0;     // 1 BTC
double fee = calculateFee(transaction, 0.0001);  // 0.0001 BTC fee
```

## Error Handling

### 1. Using Return Values
```cpp
bool sendPayment(double amount, double balance) {
    if (amount <= 0) {
        return false;  // Invalid amount
    }
    if (amount > balance) {
        return false;  // Insufficient funds
    }
    // Process payment...
    return true;
}

// Usage
if (!sendPayment(1.0, 0.5)) {
    std::cout << "Payment failed!\n";
}
```

### 2. Using Exceptions
```cpp
#include <stdexcept>

void transferFunds(double amount, double& fromBalance, double& toBalance) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }
    if (amount > fromBalance) {
        throw std::runtime_error("Insufficient funds");
    }
    
    fromBalance -= amount;
    toBalance += amount;
}

// Usage with try-catch
try {
    double account1 = 1.0;
    double account2 = 0.0;
    transferFunds(0.5, account1, account2);
} catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
```

## Practice Programs

### 1. Wallet Manager
```cpp
#include <iostream>
#include <stdexcept>

class InsufficientFundsError : public std::runtime_error {
public:
    InsufficientFundsError() : std::runtime_error("Insufficient funds") {}
};

void withdraw(double& balance, double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Invalid withdrawal amount");
    }
    if (amount > balance) {
        throw InsufficientFundsError();
    }
    balance -= amount;
}

void deposit(double& balance, double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Invalid deposit amount");
    }
    balance += amount;
}

int main() {
    double walletBalance = 1.0;  // 1 BTC
    
    try {
        std::cout << "Initial balance: " << walletBalance << " BTC\n";
        
        deposit(walletBalance, 0.5);
        std::cout << "After deposit: " << walletBalance << " BTC\n";
        
        withdraw(walletBalance, 0.2);
        std::cout << "After withdrawal: " << walletBalance << " BTC\n";
        
        // This should fail
        withdraw(walletBalance, 2.0);
        
    } catch (const InsufficientFundsError& e) {
        std::cout << "Error: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

### 2. Transaction Validator
```cpp
#include <iostream>
#include <string>

struct Transaction {
    double amount;
    std::string sender;
    std::string receiver;
};

bool validateTransaction(const Transaction& tx) {
    // Check amount
    if (tx.amount <= 0) return false;
    
    // Check sender/receiver
    if (tx.sender.empty() || tx.receiver.empty()) return false;
    if (tx.sender == tx.receiver) return false;
    
    return true;
}

void processTransaction(const Transaction& tx) {
    if (!validateTransaction(tx)) {
        throw std::invalid_argument("Invalid transaction");
    }
    
    std::cout << "Processing " << tx.amount << " BTC\n";
    std::cout << "From: " << tx.sender << "\n";
    std::cout << "To: " << tx.receiver << "\n";
}

int main() {
    Transaction tx{
        .amount = 0.5,
        .sender = "Alice",
        .receiver = "Bob"
    };
    
    try {
        processTransaction(tx);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

## Common Mistakes to Avoid

### 1. Forgetting Return Values
```cpp
// Wrong: Missing return statement
double getBalance() {
    double balance = 100.0;
    if (balance > 0) {
        return balance;
    }
    // Missing return for balance <= 0!
}

// Correct: All paths return a value
double getBalance() {
    double balance = 100.0;
    if (balance > 0) {
        return balance;
    }
    return 0.0;
}
```

### 2. Ignoring Error Cases
```cpp
// Wrong: No error handling
void processPayment(double amount) {
    // What if amount is negative?
    std::cout << "Processing " << amount << " BTC\n";
}

// Correct: With error handling
void processPayment(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Invalid amount");
    }
    std::cout << "Processing " << amount << " BTC\n";
}
```

## Knowledge Check

Try to answer these questions:
1. What are the parts of a function declaration?
2. When should you use exceptions vs return values for errors?
3. Why is error handling important in Bitcoin applications?
4. What happens if a function has no return statement?
5. How do you catch multiple types of exceptions?

## Bitcoin-Specific Function Tips

1. Always validate amounts and balances
2. Use exceptions for unexpected errors
3. Return false/error codes for expected failure cases
4. Document function requirements clearly
5. Consider edge cases (zero amounts, maximum values)

## Next Steps

1. **Experiment!** Try:
   - Creating different types of functions
   - Handling various error cases
   - Building a complete transaction system

2. **Challenge Yourself:**
   - Add more validation rules
   - Implement complex error handling
   - Create a multi-function program

3. When you're ready, move on to your first project: [Hash Calculator](../projects/01_hash_calculator.md)

Remember:
- Test all possible error cases
- Always handle errors appropriately
- Document your functions
- Keep functions focused and simple