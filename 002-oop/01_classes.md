# Classes and Encapsulation in C++

Welcome to Object-Oriented Programming! In this tutorial, you'll learn how to organize code and data using classes, with examples from Bitcoin wallet and transaction management.

## Learning Objectives
- Understand classes and objects
- Master data encapsulation
- Learn about constructors and destructors
- Practice with Bitcoin-relevant examples

## What is a Class?

A class is like a blueprint for creating objects. Think of it like a wallet design:
```cpp
class Wallet {
private:
    double balance;      // How much BTC we have
    std::string address; // Our Bitcoin address

public:
    // Functions to interact with the wallet
    void deposit(double amount);
    bool withdraw(double amount);
};
```

## Basic Class Structure

### Class Declaration
```cpp
class Transaction {
private:
    // Private members (data encapsulation)
    std::string sender;
    std::string receiver;
    double amount;
    bool isValid;

public:
    // Public interface
    Transaction(std::string from, std::string to, double value);
    bool validate();
    void execute();
};
```

### Implementation
```cpp
// Constructor
Transaction::Transaction(std::string from, std::string to, double value) 
    : sender(from), receiver(to), amount(value), isValid(false) {
}

bool Transaction::validate() {
    // Validation logic
    isValid = (amount > 0 && sender != receiver);
    return isValid;
}

void Transaction::execute() {
    if (!isValid) {
        throw std::runtime_error("Cannot execute invalid transaction");
    }
    // Execute transaction logic
}
```

## Practice Program: Basic Wallet

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class BitcoinWallet {
private:
    double balance;
    std::string publicKey;
    std::vector<std::string> transactionHistory;

    // Private helper function
    void recordTransaction(const std::string& type, double amount) {
        transactionHistory.push_back(
            type + ": " + std::to_string(amount) + " BTC"
        );
    }

public:
    // Constructor
    BitcoinWallet(const std::string& pubKey) 
        : balance(0.0), publicKey(pubKey) {
    }

    // Public methods
    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        balance += amount;
        recordTransaction("Deposit", amount);
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        recordTransaction("Withdrawal", amount);
        return true;
    }

    // Getters
    double getBalance() const {
        return balance;
    }

    std::string getAddress() const {
        return publicKey;
    }

    void printHistory() const {
        std::cout << "Transaction History for " << publicKey << ":\n";
        for (const auto& transaction : transactionHistory) {
            std::cout << "- " << transaction << "\n";
        }
    }
};

int main() {
    try {
        // Create a new wallet
        BitcoinWallet wallet("1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa");

        // Test wallet operations
        std::cout << "New wallet created with address: " 
                  << wallet.getAddress() << "\n";

        wallet.deposit(1.5);  // Deposit 1.5 BTC
        std::cout << "Balance after deposit: " 
                  << wallet.getBalance() << " BTC\n";

        if (wallet.withdraw(0.5)) {  // Withdraw 0.5 BTC
            std::cout << "Withdrawal successful\n";
        }
        std::cout << "Final balance: " 
                  << wallet.getBalance() << " BTC\n";

        wallet.printHistory();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

## Key Concepts

### 1. Encapsulation
```cpp
class PrivateKey {
private:
    std::vector<uint8_t> keyData;  // Private data

public:
    bool sign(const std::vector<uint8_t>& message);  // Public interface
};
```

### 2. Constructors
```cpp
class Block {
private:
    uint32_t height;
    std::string prevHash;

public:
    // Default constructor
    Block() : height(0), prevHash("") {}

    // Parameterized constructor
    Block(uint32_t h, std::string prev) 
        : height(h), prevHash(prev) {}
};
```

### 3. Destructors
```cpp
class SecureWallet {
private:
    std::vector<uint8_t> privateKeyData;

public:
    ~SecureWallet() {
        // Secure cleanup in destructor
        std::fill(privateKeyData.begin(), 
                 privateKeyData.end(), 0);
    }
};
```

## Practice Exercises

### 1. Create a Transaction Class
```cpp
class Transaction {
private:
    std::string txid;
    double amount;
    std::string sender;
    std::string recipient;
    bool confirmed;

public:
    Transaction(std::string from, std::string to, double value);
    bool confirm();
    std::string getTxid() const;
    // Add more methods
};
```

### 2. Implement a Block Class
```cpp
class Block {
private:
    uint32_t version;
    std::string prevBlockHash;
    std::string merkleRoot;
    uint32_t timestamp;
    uint32_t bits;
    uint32_t nonce;
    std::vector<Transaction> transactions;

public:
    Block(uint32_t ver, std::string prev);
    void addTransaction(const Transaction& tx);
    bool mine(uint32_t difficulty);
    // Add more methods
};
```

## Common Mistakes to Avoid

### 1. Public Data Members
```cpp
// Wrong: Public data
class BadWallet {
public:
    double balance;  // Anyone can modify!
};

// Correct: Private data with public interface
class GoodWallet {
private:
    double balance;
public:
    double getBalance() const;
    void deposit(double amount);
};
```

### 2. Missing Const Correctness
```cpp
// Wrong: Missing const
class Wallet {
    double getBalance() { return balance; }
};

// Correct: Use const for read-only methods
class Wallet {
    double getBalance() const { return balance; }
};
```

### 3. Poor Encapsulation
```cpp
// Wrong: Exposing internal details
class Transaction {
public:
    std::vector<uint8_t> rawData;  // Should be private!
};

// Correct: Provide controlled access
class Transaction {
private:
    std::vector<uint8_t> rawData;
public:
    bool verify() const;
    std::string getHash() const;
};
```

## Knowledge Check

Try to answer these questions:
1. What is encapsulation and why is it important?
2. When do you need a destructor?
3. What's the difference between public and private members?
4. Why use getters and setters?
5. How does const correctness help in class design?

## Bitcoin-Specific Tips

1. Always protect sensitive data (private keys, seeds)
2. Use const methods for queries that don't modify state
3. Implement secure cleanup in destructors
4. Validate all inputs in public methods
5. Keep transaction data immutable after creation

## Next Steps

1. **Experiment with:**
   - Creating different wallet types
   - Implementing transaction classes
   - Building block structures

2. **Challenge Yourself:**
   - Add more security features
   - Implement multi-signature wallets
   - Create a transaction pool class

3. When you're ready, move on to [Inheritance and Polymorphism](02_inheritance.md)

Remember:
- Keep data private
- Validate all inputs
- Clean up sensitive data
- Use const when appropriate
- Document your class interfaces