# Functions and Error Handling in C++

<details>
<summary>📚 Module Information</summary>

**Difficulty Level:** ⭐⭐ (Intermediate)  
**Time to Complete:** ~40 minutes  
**Prerequisites:** Variables, Control Flow, Memory Basics

This module covers functions and error handling in C++, essential skills for writing maintainable and robust Bitcoin applications.
</details>

## Learning Objectives
By the end of this module, you will be able to:
- Create and use functions effectively in C++
- Implement proper error handling mechanisms
- Write robust Bitcoin-related functions
- Use exceptions appropriately
- Debug function-related issues

## Function Fundamentals

<details>
<summary>🔨 Basic Function Concepts</summary>

### What is a Function?
A function is a reusable block of code that performs a specific task:
```cpp
// Simple function that validates a Bitcoin amount
bool isValidAmount(double amount) {
    return amount > 0 && amount <= 21000000;
}
```

### Function Components
1. **Return Type:** What the function gives back
2. **Name:** What the function is called
3. **Parameters:** Input values
4. **Body:** The actual code
```cpp
// Return type | Name | Parameters
   double      add    (double a, double b) {
       return a + b;  // Body with return
   }
```

### Function Types
1. **Value-returning functions**
```cpp
double calculateFee(double amount) {
    return amount * 0.0001;  // Returns 0.01% fee
}
```

2. **Void functions**
```cpp
void logTransaction(const std::string& txId) {
    std::cout << "Processing transaction: " << txId << "\n";
}
```

3. **Reference parameters**
```cpp
void updateBalance(double& balance, double amount) {
    balance += amount;
}
```
</details>

## Error Handling

<details>
<summary>⚠️ Error Handling Techniques</summary>

### 1. Return Values
```cpp
bool processPayment(double amount, double& balance) {
    if (amount <= 0) return false;
    if (amount > balance) return false;
    balance -= amount;
    return true;
}
```

### 2. Exceptions
```cpp
class InsufficientFundsError : public std::runtime_error {
public:
    InsufficientFundsError() 
        : std::runtime_error("Insufficient funds") {}
};

void transfer(double& from, double& to, double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Invalid amount");
    }
    if (amount > from) {
        throw InsufficientFundsError();
    }
    from -= amount;
    to += amount;
}
```

### 3. Error Codes
```cpp
enum class TransactionError {
    Success,
    InvalidAmount,
    InsufficientFunds,
    NetworkError
};

TransactionError sendBitcoin(double amount) {
    if (amount <= 0) return TransactionError::InvalidAmount;
    if (amount > balance) return TransactionError::InsufficientFunds;
    // ... send transaction ...
    return TransactionError::Success;
}
```
</details>

## Bitcoin-Specific Functions

<details>
<summary>₿ Bitcoin Development Examples</summary>

### 1. Transaction Validation
```cpp
struct Transaction {
    double amount;
    std::string sender;
    std::string receiver;
    double fee;
};

bool validateTransaction(const Transaction& tx) {
    // Amount validation
    if (tx.amount <= 0 || tx.amount > 21000000) {
        return false;
    }
    
    // Fee validation
    if (tx.fee < 0 || tx.fee > tx.amount) {
        return false;
    }
    
    // Address validation
    if (tx.sender.empty() || tx.receiver.empty()) {
        return false;
    }
    
    return true;
}
```

### 2. Wallet Management
```cpp
class Wallet {
private:
    double balance;
    std::vector<Transaction> history;

public:
    // Safe balance update
    void updateBalance(double amount) {
        if (std::isfinite(amount)) {  // Check for valid number
            balance += amount;
        } else {
            throw std::invalid_argument("Invalid amount");
        }
    }
    
    // Safe transaction processing
    bool processTransaction(const Transaction& tx) {
        try {
            if (!validateTransaction(tx)) {
                return false;
            }
            updateBalance(-tx.amount - tx.fee);
            history.push_back(tx);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Transaction failed: " << e.what() << "\n";
            return false;
        }
    }
};
```
</details>

## Knowledge Check

<details>
<summary>🤔 Test Your Understanding</summary>

### Question 1: Function Parameters
What's wrong with this function?
```cpp
void updateWalletBalance(double balance, double amount) {
    balance += amount;
}

int main() {
    double walletBalance = 100.0;
    updateWalletBalance(walletBalance, 50.0);
    std::cout << walletBalance;  // Still 100.0!
}
```
<details>
<summary>👉 Click to see answer</summary>

- ❌ The function name is incorrect
- ✅ Parameter should be passed by reference
- ❌ The addition is wrong
- ❌ Nothing is wrong

**Explanation:** The function takes `balance` by value, creating a copy. To modify the original balance, it should use a reference parameter: `void updateWalletBalance(double& balance, double amount)`.
</details>

### Question 2: Error Handling
Which error handling approach is best for this scenario?
```cpp
void processLargeTransaction(double amount) {
    // Method A: Return bool
    // Method B: Throw exception
    // Method C: Return error code
}
```
<details>
<summary>👉 Click to see answer</summary>

- ✅ Throw exception (Method B)
- ❌ Return bool (Method A)
- ❌ Return error code (Method C)

**Explanation:** Large transactions are exceptional cases that can fail for multiple reasons (insufficient funds, network issues, validation errors). Exceptions provide:
1. Detailed error information
2. Cannot be ignored (unlike return values)
3. Automatic propagation up the call stack
</details>

### Question 3: Function Design
Analyze this Bitcoin transaction function:
```cpp
bool sendBitcoin(std::string from, std::string to, double amount) {
    if (from == "") return false;
    if (to == "") return false;
    if (amount < 0) return false;
    // ... send bitcoin ...
    return true;
}
```
What could be improved?
<details>
<summary>👉 Click to see answer</summary>

Improvements needed:
- ✅ Use references for strings (`const std::string&`)
- ✅ Add more specific error handling
- ✅ Validate maximum amount
- ✅ Add proper address format validation
- ❌ Change return type to void

**Better Version:**
```cpp
enum class TxError {
    Success,
    InvalidSender,
    InvalidReceiver,
    InvalidAmount,
    NetworkError
};

TxError sendBitcoin(const std::string& from, 
                    const std::string& to, 
                    double amount) {
    if (!isValidAddress(from)) return TxError::InvalidSender;
    if (!isValidAddress(to)) return TxError::InvalidReceiver;
    if (amount <= 0 || amount > 21000000) {
        return TxError::InvalidAmount;
    }
    // ... send bitcoin ...
    return TxError::Success;
}
```
</details>

### Question 4: Exception Safety
What's wrong with this error handling?
```cpp
void processPayment(double& balance, double amount) {
    balance -= amount;  // Deduct first
    if (amount <= 0) {
        throw std::invalid_argument("Invalid amount");
    }
    if (amount > balance) {
        throw std::runtime_error("Insufficient funds");
    }
}
```
<details>
<summary>👉 Click to see answer</summary>

Issues:
- ✅ Balance is modified before validation
- ✅ No exception safety guarantee
- ✅ Potential negative balance
- ❌ Wrong exception types

**Better Version:**
```cpp
void processPayment(double& balance, double amount) {
    // Validate first
    if (amount <= 0) {
        throw std::invalid_argument("Invalid amount");
    }
    if (amount > balance) {
        throw std::runtime_error("Insufficient funds");
    }
    // Modify after validation
    balance -= amount;
}
```
</details>

### Question 5: Function Overloading
Which overload will be called?
```cpp
void processAmount(int amount) { std::cout << "int\n"; }
void processAmount(double amount) { std::cout << "double\n"; }
void processAmount(long amount) { std::cout << "long\n"; }

int main() {
    processAmount(42.0f);
}
```
<details>
<summary>👉 Click to see answer</summary>

- ❌ int version
- ✅ double version
- ❌ long version
- ❌ Compilation error

**Explanation:** The `float` argument (42.0f) will be promoted to `double`, calling the double version. This is important in Bitcoin applications where precision matters!
</details>
</details>

## Practice Exercises

<details>
<summary>💻 Hands-on Practice</summary>

### Exercise 1: Basic Transaction Handler (⭐ Beginner)
Create functions to handle basic Bitcoin transactions.

<details>
<summary>👉 Requirements</summary>

1. Implement transaction validation
2. Handle basic error cases
3. Track transaction history
4. Use appropriate error handling
</details>

<details>
<summary>👉 Solution Framework</summary>

```cpp
struct Transaction {
    std::string sender;
    std::string receiver;
    double amount;
};

class TransactionHandler {
private:
    std::vector<Transaction> history;

public:
    bool validateTransaction(const Transaction& tx) {
        // Your validation code here
        return false;
    }
    
    void processTransaction(const Transaction& tx) {
        // Your processing code here
    }
};
```
</details>

### Exercise 2: Wallet Functions (⭐⭐ Intermediate)
Implement a wallet system with proper error handling.

<details>
<summary>👉 Requirements</summary>

1. Support deposits and withdrawals
2. Implement proper error handling
3. Track transaction history
4. Add balance validation
5. Use exceptions appropriately
</details>

### Exercise 3: Advanced Transaction System (⭐⭐⭐ Advanced)
Build a comprehensive transaction system with advanced error handling.

<details>
<summary>👉 Requirements</summary>

1. Implement multi-signature support
2. Add transaction fee calculation
3. Handle network errors
4. Implement rollback mechanism
5. Add comprehensive logging
</details>
</details>

## Next Steps

<details>
<summary>🎯 Moving Forward</summary>

### What You've Learned
- Function creation and usage
- Error handling techniques
- Bitcoin-specific function design
- Exception safety
- Best practices

### Where to Go Next
1. Complete the practice exercises
2. Review the knowledge check questions
3. Experiment with the code examples
4. Move on to [Classes and Objects](06_classes.md)

### Additional Resources
- [C++ Functions Reference](https://en.cppreference.com/w/cpp/language/functions)
- [Exception Handling Guide](https://en.cppreference.com/w/cpp/language/exceptions)
- [Bitcoin Development Resources](https://bitcoin.org/en/development)
</details>