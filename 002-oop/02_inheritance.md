# Inheritance and Polymorphism in C++

Welcome to the second OOP tutorial! Here you'll learn how to create hierarchies of related classes and work with different types of transactions and wallets.

## Learning Objectives
- Understand inheritance and its uses
- Master polymorphism concepts
- Learn about virtual functions
- Practice with Bitcoin transaction types

## What is Inheritance?

Inheritance allows you to create new classes based on existing ones. Think of different types of Bitcoin transactions:
```cpp
// Base transaction type
class Transaction {
protected:
    std::string txid;
    double amount;
    
public:
    virtual bool validate() = 0;  // Pure virtual function
};

// Specific transaction type
class PaymentTransaction : public Transaction {
private:
    std::string recipient;
    
public:
    bool validate() override {
        return amount > 0;
    }
};
```

## Basic Inheritance

### Base Class
```cpp
class Wallet {
protected:
    double balance;
    std::string address;

public:
    Wallet(const std::string& addr) 
        : balance(0), address(addr) {}
    
    virtual bool send(double amount, const std::string& to) = 0;
    virtual void receive(double amount) = 0;
    
    double getBalance() const { return balance; }
};
```

### Derived Classes
```cpp
class BasicWallet : public Wallet {
public:
    BasicWallet(const std::string& addr) : Wallet(addr) {}
    
    bool send(double amount, const std::string& to) override {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
    
    void receive(double amount) override {
        balance += amount;
    }
};

class MultiSigWallet : public Wallet {
private:
    std::vector<std::string> signers;
    size_t requiredSignatures;

public:
    MultiSigWallet(const std::string& addr, 
                   const std::vector<std::string>& signers,
                   size_t required)
        : Wallet(addr), signers(signers), 
          requiredSignatures(required) {}
    
    bool send(double amount, const std::string& to) override {
        // Would require multiple signatures in real implementation
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
    
    void receive(double amount) override {
        balance += amount;
    }
};
```

## Practice Program: Transaction System

```cpp
#include <iostream>
#include <vector>
#include <memory>

// Base Transaction Class
class Transaction {
protected:
    std::string txid;
    double amount;
    std::string sender;
    bool verified;

public:
    Transaction(const std::string& id, double amt, const std::string& from)
        : txid(id), amount(amt), sender(from), verified(false) {}
    
    virtual ~Transaction() = default;
    
    // Pure virtual functions
    virtual bool verify() = 0;
    virtual void execute() = 0;
    
    // Common functionality
    std::string getTxid() const { return txid; }
    double getAmount() const { return amount; }
};

// Regular Payment Transaction
class PaymentTransaction : public Transaction {
private:
    std::string recipient;

public:
    PaymentTransaction(const std::string& id, double amt,
                      const std::string& from, const std::string& to)
        : Transaction(id, amt, from), recipient(to) {}
    
    bool verify() override {
        verified = (amount > 0 && sender != recipient);
        return verified;
    }
    
    void execute() override {
        if (!verified) {
            throw std::runtime_error("Unverified transaction");
        }
        std::cout << "Executing payment: " << amount 
                  << " BTC from " << sender 
                  << " to " << recipient << "\n";
    }
};

// Multi-signature Transaction
class MultiSigTransaction : public Transaction {
private:
    std::vector<std::string> requiredSigners;
    std::vector<std::string> signatures;

public:
    MultiSigTransaction(const std::string& id, double amt,
                       const std::string& from,
                       const std::vector<std::string>& signers)
        : Transaction(id, amt, from), requiredSigners(signers) {}
    
    void addSignature(const std::string& signature) {
        signatures.push_back(signature);
    }
    
    bool verify() override {
        verified = (signatures.size() >= requiredSigners.size());
        return verified;
    }
    
    void execute() override {
        if (!verified) {
            throw std::runtime_error("Insufficient signatures");
        }
        std::cout << "Executing multi-sig transaction: " 
                  << amount << " BTC\n";
    }
};

// Transaction Manager
class TransactionManager {
private:
    std::vector<std::unique_ptr<Transaction>> transactions;

public:
    void addTransaction(std::unique_ptr<Transaction> tx) {
        transactions.push_back(std::move(tx));
    }
    
    void processTransactions() {
        for (auto& tx : transactions) {
            try {
                if (tx->verify()) {
                    tx->execute();
                } else {
                    std::cout << "Transaction " << tx->getTxid() 
                              << " failed verification\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error processing transaction: " 
                          << e.what() << "\n";
            }
        }
    }
};

int main() {
    TransactionManager manager;
    
    // Create different types of transactions
    auto payment = std::make_unique<PaymentTransaction>(
        "tx1", 1.5, "Alice", "Bob"
    );
    
    auto multiSig = std::make_unique<MultiSigTransaction>(
        "tx2", 2.0, "Charlie",
        std::vector<std::string>{"Alice", "Bob", "Charlie"}
    );
    
    // Add signatures to multi-sig transaction
    multiSig->addSignature("Alice_sig");
    multiSig->addSignature("Bob_sig");
    multiSig->addSignature("Charlie_sig");
    
    // Add transactions to manager
    manager.addTransaction(std::move(payment));
    manager.addTransaction(std::move(multiSig));
    
    // Process all transactions
    manager.processTransactions();
    
    return 0;
}
```

## Key Concepts

### 1. Virtual Functions
```cpp
class Transaction {
public:
    virtual bool verify() = 0;  // Pure virtual
    virtual void execute() { }  // Virtual with default
    virtual ~Transaction() { }  // Virtual destructor
};
```

### 2. Override Keyword
```cpp
class SegWitTransaction : public Transaction {
public:
    bool verify() override {  // Explicitly marked override
        // Verification logic
        return true;
    }
};
```

### 3. Protected Access
```cpp
class Wallet {
protected:  // Accessible to derived classes
    double balance;
    std::string address;
};
```

## Practice Exercises

### 1. Create Different Transaction Types
```cpp
// Base class
class Transaction {
    // ... base implementation
};

// Derived classes
class LegacyTransaction : public Transaction {
    // ... legacy format
};

class SegWitTransaction : public Transaction {
    // ... segregated witness format
};

class TaprootTransaction : public Transaction {
    // ... taproot format
};
```

### 2. Implement Wallet Hierarchy
```cpp
class Wallet {
    // Base wallet functionality
};

class HotWallet : public Wallet {
    // Online wallet implementation
};

class ColdWallet : public Wallet {
    // Offline wallet implementation
};

class WatchOnlyWallet : public Wallet {
    // Read-only wallet implementation
};
```

## Common Mistakes to Avoid

### 1. Forgetting Virtual Destructor
```cpp
// Wrong: Missing virtual destructor
class Transaction {
    ~Transaction() { }  // Not virtual!
};

// Correct:
class Transaction {
    virtual ~Transaction() { }
};
```

### 2. Slicing Objects
```cpp
// Wrong: Object slicing
Transaction tx = PaymentTransaction(...);  // Slices object

// Correct: Use pointers or references
std::unique_ptr<Transaction> tx = 
    std::make_unique<PaymentTransaction>(...);
```

### 3. Not Using Override
```cpp
// Wrong: Missing override
class PaymentTransaction : public Transaction {
    bool verify() { }  // Did we mean to override?
};

// Correct:
class PaymentTransaction : public Transaction {
    bool verify() override { }
};
```

## Knowledge Check

Try to answer these questions:
1. What is the difference between inheritance and composition?
2. When should you use virtual functions?
3. What is a pure virtual function?
4. Why do we need virtual destructors?
5. What is object slicing and how do we avoid it?

## Bitcoin-Specific Tips

1. Use inheritance for different transaction types
2. Implement strong validation in derived classes
3. Consider using factory patterns for transaction creation
4. Use polymorphism for transaction processing
5. Keep security-critical code in base classes

## Next Steps

1. **Experiment with:**
   - Creating more transaction types
   - Implementing different wallet types
   - Building transaction processors

2. **Challenge Yourself:**
   - Add support for complex script types
   - Implement transaction signing
   - Create a transaction verification system

3. When you're ready, move on to the [Wallet Structure Project](../projects/02_wallet.md)

Remember:
- Always use virtual destructors
- Mark overrides explicitly
- Use smart pointers for polymorphic objects
- Consider security implications
- Test all derived classes thoroughly 