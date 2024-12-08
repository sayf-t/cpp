# Memory and References in C++

<details>
<summary>📚 Module Information</summary>

**Difficulty Level:** ⭐⭐⭐ (Intermediate)  
**Time to Complete:** ~45 minutes  
**Prerequisites:** Variables and Types module

This module covers essential concepts of memory management and references in C++, crucial skills for Bitcoin development where memory safety and efficiency are paramount.
</details>

## Learning Objectives
By the end of this module, you will be able to:
- Understand how computer memory works and its role in C++ programs
- Differentiate between stack and heap memory allocation
- Master the use of references for efficient memory management
- Apply memory safety principles in Bitcoin-related code
- Implement proper memory management in transaction handling

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

## Memory Types in C++

### Stack vs Heap Memory
The stack and heap are two fundamental types of memory in C++:

1. **Stack Memory:**
   - Automatically managed memory (allocates and deallocates automatically)
   - Fast access and cleanup
   - Limited in size
   - Used for local variables and function calls
   - Memory is cleaned up when variables go out of scope

```cpp
void example() {
    int x = 5;        // Stack allocation
    double y = 3.14;  // Stack allocation
}  // x and y automatically cleaned up here
```

2. **Heap Memory:**
   - Manually managed memory (you control allocation and deallocation)
   - Slower than stack memory
   - Limited only by system memory
   - Used for dynamic allocation
   - Must be manually cleaned up to prevent memory leaks

```cpp
int* ptr = new int(5);  // Heap allocation
// ... use ptr ...
delete ptr;             // Manual cleanup required
```

## Why Use References?

References provide several key benefits over copying values:

1. **Performance:** Avoid copying large objects
```cpp
// Inefficient - copies entire vector
void processData(std::vector<int> data) { /*...*/ }

// Efficient - uses reference, no copy
void processData(const std::vector<int>& data) { /*...*/ }
```

2. **Modification:** Ability to modify original values
```cpp
void addFunds(double& balance) {
    balance += 100;  // Modifies original balance
}
```

3. **Memory Efficiency:** Save memory by not duplicating data
```cpp
struct LargeObject { 
    double data[10000]; 
};

// Reference prevents copying 10000 doubles
void analyze(const LargeObject& obj) { /*...*/ }
```

## Const References: When and Why

Use const references when you:
1. Want to prevent modifications to the original data
2. Need to avoid expensive copies
3. Want to ensure function safety

Example of proper const reference usage:
```cpp
// Safe: amount can't be modified
void verifyPayment(const double& amount) {
    if (amount > 0) {
        std::cout << "Valid amount\n";
    }
}

// Unsafe: could accidentally modify amount
void verifyPayment(double& amount) {
    amount = 0;  // Oops! Modified the original
}
```

## Reference Safety

Key points about reference safety:

1. **References Cannot Be Null**
```cpp
int x = 5;
int& ref = x;     // Valid reference
// int& ref = nullptr;  // Error: references can't be null
```

2. **References Must Be Initialized**
```cpp
int x = 5;
int& ref = x;     // Good: initialized immediately
// int& badRef;   // Error: references must be initialized
```

## Memory Safety in Bitcoin Applications

Memory safety is crucial in Bitcoin applications because:

1. **Financial Security:**
   - Memory errors could lead to fund loss
   - Corrupted memory could compromise private keys
   - Transaction data must remain unmodified

2. **Data Integrity:**
   - Wallet balances must be accurate
   - Transaction history must be preserved
   - Smart contracts must execute precisely

Example of secure Bitcoin transaction handling:
```cpp
bool processTransaction(const double& amount, 
                      const std::string& privateKey) {
    // Private key is protected from modification
    // Amount cannot be tampered with
    return validateAndExecute(amount, privateKey);
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

<details>
<summary>🤔 Test Your Understanding</summary>

### Question 1: Memory Allocation
Given this code:
```cpp
void processWallet() {
    double balance = 100.0;
    double* dynamicBalance = new double(200.0);
    // ... some operations ...
}
```
Which statement is correct about memory management?
<details>
<summary>👉 Click to see answer</summary>

- ✅ `balance` is automatically cleaned up when the function ends
- ✅ `dynamicBalance` needs manual cleanup with `delete`
- ❌ Both variables are automatically cleaned up
- ❌ Both variables need manual cleanup

**Explanation:** Stack variables like `balance` are automatically managed, while heap memory allocated with `new` must be manually freed with `delete` to prevent memory leaks. In Bitcoin applications, memory leaks could lead to resource exhaustion during long-running operations.
</details>

### Question 2: Reference Safety
Consider this code:
```cpp
void updateBalance(double& balance) {
    balance += 50.0;
}

int main() {
    double walletA = 100.0;
    updateBalance(walletA);
    return 0;
}
```
What makes this code memory-safe?
<details>
<summary>👉 Click to see answer</summary>

- ✅ The reference is guaranteed to be valid
- ✅ No dynamic memory allocation is needed
- ✅ The reference must be initialized
- ❌ References can be null

**Explanation:** References in C++ provide memory safety by requiring initialization and always referring to valid objects. This is particularly important in Bitcoin applications where we need guaranteed access to wallet balances and transaction data.
</details>

### Question 3: Const Correctness
Examine this transaction validation code:
```cpp
bool validateTransaction(const double& amount, const std::string& txId) {
    // Validation logic
    return amount > 0;
}
```
Why use `const` references here?
<details>
<summary>👉 Click to see answer</summary>

- ✅ Prevents accidental modification of transaction data
- ✅ Provides better performance than passing by value
- ✅ Makes the function's intent clear
- ❌ Allows the function to modify the parameters

**Explanation:** Using `const` references in transaction validation ensures data integrity while maintaining performance. This is crucial in Bitcoin applications where transaction data must remain immutable during validation.
</details>

### Question 4: Memory Leaks
What's wrong with this wallet implementation?
```cpp
class Wallet {
    double* balance;
public:
    Wallet() { balance = new double(0.0); }
    void deposit(double amount) { *balance += amount; }
};
```
<details>
<summary>👉 Click to see answer</summary>

- ✅ Missing destructor leads to memory leak
- ✅ No copy constructor for safe copying
- ✅ No assignment operator for safe assignment
- ❌ Using pointers for balance is optimal

**Explanation:** This implementation violates the Rule of Three and leaks memory. In Bitcoin applications, memory leaks could accumulate during long-running operations, potentially affecting system stability and security.

**Correct Implementation:**
```cpp
class Wallet {
    double* balance;
public:
    Wallet() : balance(new double(0.0)) {}
    ~Wallet() { delete balance; }
    Wallet(const Wallet& other) : balance(new double(*other.balance)) {}
    Wallet& operator=(const Wallet& other) {
        if (this != &other) {
            *balance = *other.balance;
        }
        return *this;
    }
    void deposit(double amount) { *balance += amount; }
};
```
</details>

### Question 5: Practical Application
You're implementing a multi-signature wallet feature. Which memory management approach is most appropriate?
<details>
<summary>👉 Click to see answer</summary>

```cpp
class MultiSigWallet {
    std::vector<std::string> signatures;  // Using STL container
    double balance;
public:
    bool addSignature(const std::string& sig) {
        if (signatures.size() < 3) {  // Assuming 3-of-3 multisig
            signatures.push_back(sig);
            return true;
        }
        return false;
    }
};
```

**Best Practices Demonstrated:**
- ✅ Using STL containers for automatic memory management
- ✅ Taking signatures by const reference
- ✅ No manual memory management needed
- ✅ Exception-safe implementation

**Explanation:** This implementation leverages C++'s standard library for safe memory management, crucial for handling cryptographic signatures in Bitcoin applications.
</details>
</details>

## Practice Exercises

<details>
<summary>💻 Hands-on Practice</summary>

### Exercise 1: Safe Transaction Handler (⭐ Beginner)
Implement a basic transaction handler with proper memory management.

### Exercise 2: Multi-Wallet Manager (⭐⭐ Intermediate)
Create a system for managing multiple wallets with proper reference handling.

### Exercise 3: Advanced Memory Safety (⭐⭐⭐ Advanced)
Implement a thread-safe wallet system with proper memory management.

[Previous exercises and solutions remain as is...]
</details>

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

## Memory Concepts

<details>
<summary>🧠 Core Memory Concepts</summary>

### Stack Memory
- Fast, automatic memory management
- Fixed size, determined at compile time
- Perfect for local variables
- Automatically cleaned up

### Heap Memory
- Dynamic, flexible memory allocation
- Manual management required
- Larger capacity than stack
- Must be explicitly freed

### Memory Safety Rules
1. Always initialize variables
2. Clean up heap memory
3. Use smart pointers when possible
4. Avoid dangling references
</details>

## References in C++

<details>
<summary>🔗 Understanding References</summary>

### What are References?
References provide an alias to an existing variable:
```cpp
int value = 42;
int& ref = value;  // ref is now an alias for value
```

### Key Properties
1. Must be initialized when declared
2. Cannot be null
3. Cannot be reassigned
4. Always refer to valid memory

### Common Use Cases
1. Function parameters
2. Avoiding copies
3. Modifying original values
4. Working with large objects
</details>

## Memory Safety in Bitcoin Development

<details>
<summary>🔒 Bitcoin-Specific Memory Practices</summary>

### Critical Considerations
1. **Private Key Safety**
   ```cpp
   class PrivateKey {
       std::array<uint8_t, 32> key_data;  // Fixed-size array for safety
   public:
       // Const reference prevents key exposure
       bool verify(const std::string& message) const {
           return validateSignature(message, key_data);
       }
   };
   ```

2. **Transaction Safety**
   ```cpp
   class Transaction {
       const double amount;  // Immutable after construction
       std::string txId;
   public:
       Transaction(double amt) : amount(amt) {}  // Initialize in constructor
       
       // Safe access through const reference
       const double& getAmount() const { return amount; }
   };
   ```

3. **Wallet Management**
   ```cpp
   class SecureWallet {
       std::vector<Transaction> history;  // Automatic memory management
   public:
       // Safe transaction processing
       bool processTransaction(const Transaction& tx) {
           history.push_back(tx);  // Vector handles memory
           return true;
       }
   };
   ```
</details>

## Best Practices

<details>
<summary>✨ Memory Management Best Practices</summary>

### 1. Use Smart Pointers
```cpp
// Instead of raw pointers:
Transaction* tx = new Transaction(100.0);
// ... code ...
delete tx;

// Use smart pointers:
std::unique_ptr<Transaction> tx = 
    std::make_unique<Transaction>(100.0);
// Automatically deleted when out of scope
```

### 2. RAII (Resource Acquisition Is Initialization)
```cpp
class WalletLock {
    std::mutex& mtx;
public:
    WalletLock(std::mutex& m) : mtx(m) { mtx.lock(); }
    ~WalletLock() { mtx.unlock(); }
};
```

### 3. Const Correctness
```cpp
class Balance {
    double amount;
public:
    // Read-only access
    const double& getAmount() const { return amount; }
    
    // Modification with validation
    bool setAmount(const double& newAmount) {
        if (newAmount >= 0) {
            amount = newAmount;
            return true;
        }
        return false;
    }
};
```
</details>

## Common Pitfalls

<details>
<summary>⚠️ Memory Management Pitfalls</summary>

### 1. Memory Leaks
```cpp
// BAD: Memory leak
void processPayment() {
    auto* payment = new Payment(100.0);
    if (validateAmount()) {
        return;  // Leaks payment object
    }
    delete payment;
}

// GOOD: RAII
void processPayment() {
    auto payment = std::make_unique<Payment>(100.0);
    if (validateAmount()) {
        return;  // payment automatically cleaned up
    }
}
```

### 2. Dangling References
```cpp
// BAD: Dangling reference
int& getDangling() {
    int local = 42;
    return local;  // Returns reference to destroyed variable
}

// GOOD: Return by value
int getSafe() {
    int local = 42;
    return local;  // Returns a copy
}
```

### 3. Double Deletion
```cpp
// BAD: Double deletion
Transaction* tx = new Transaction(50.0);
delete tx;
delete tx;  // Crash!

// GOOD: Use smart pointers
auto tx = std::make_unique<Transaction>(50.0);
// Automatically deleted exactly once
```
</details>

## Practice Exercises

<details>
<summary>💻 Coding Exercises</summary>

### Exercise 1: Safe Transaction Handler (⭐ Beginner)
Create a transaction handler that safely manages memory for Bitcoin transactions.

<details>
<summary>👉 Requirements</summary>

1. Create a `Transaction` class with:
   - Amount (double)
   - Timestamp (std::time_t)
   - Transaction ID (string)
2. Implement proper memory management
3. Use const references where appropriate
4. Add validation for amounts
</details>

<details>
<summary>👉 Solution Framework</summary>

```cpp
class Transaction {
private:
    double amount;
    std::time_t timestamp;
    std::string txId;

public:
    // Constructor
    Transaction(double amt, std::string id)
        : amount(amt)
        , timestamp(std::time(nullptr))
        , txId(std::move(id)) {}
    
    // Const getters
    const double& getAmount() const { return amount; }
    const std::string& getId() const { return txId; }
};

class TransactionHandler {
private:
    std::vector<Transaction> transactions;

public:
    bool processTransaction(const Transaction& tx) {
        if (tx.getAmount() <= 0) return false;
        transactions.push_back(tx);
        return true;
    }
};
```
</details>

### Exercise 2: Multi-Wallet Manager (⭐⭐ Intermediate)
Implement a wallet management system with proper memory safety.

<details>
<summary>👉 Requirements</summary>

1. Support multiple wallets
2. Handle transactions between wallets
3. Maintain transaction history
4. Ensure thread safety
5. Prevent memory leaks
</details>

### Exercise 3: Advanced Memory Safety (⭐⭐⭐ Advanced)
Build a thread-safe wallet system with advanced memory management.

<details>
<summary>👉 Requirements</summary>

1. Implement multi-signature support
2. Handle concurrent transactions
3. Use smart pointers
4. Implement RAII
5. Add comprehensive error handling
</details>
</details>

## Next Steps

<details>
<summary>🎯 Moving Forward</summary>

### What You've Learned
- Memory management fundamentals
- Reference usage and safety
- Bitcoin-specific memory considerations
- Best practices for memory safety

### Where to Go Next
1. Complete the practice exercises
2. Review the knowledge check questions
3. Experiment with the code examples
4. Move on to [Functions and Error Handling](05_functions.md)

### Additional Resources
- [C++ Memory Model](https://en.cppreference.com/w/cpp/language/memory_model)
- [Smart Pointers Guide](https://en.cppreference.com/w/cpp/memory)
- [RAII and Memory Safety](https://en.cppreference.com/w/cpp/language/raii)
</details>