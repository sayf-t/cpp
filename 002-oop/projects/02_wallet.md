# Project 2: Building a Wallet Structure

Welcome to your second C++ project! We'll build a comprehensive wallet system that demonstrates object-oriented programming concepts in a Bitcoin context.

## Learning Objectives
- Apply inheritance and polymorphism
- Implement secure wallet management
- Practice exception handling
- Use smart pointers and RAII

## What We're Building

A wallet management system that supports:
- Different wallet types (Basic, MultiSig, Watch-Only)
- Transaction handling
- Balance management
- Basic key management
- Transaction history

## Project Structure

```
wallet_system/
├── wallet.h           // Base wallet class
├── basic_wallet.h     // Basic wallet implementation
├── multisig_wallet.h  // Multi-signature wallet
├── watch_wallet.h     // Watch-only wallet
├── transaction.h      // Transaction classes
└── main.cpp          // Demo program
```

## Step-by-Step Implementation

### Step 1: Base Wallet Interface

Create `wallet.h`:
```cpp
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

// Forward declaration
class Transaction;

class Wallet {
protected:
    double balance;
    std::string address;
    std::vector<std::shared_ptr<Transaction>> transactionHistory;

public:
    Wallet(const std::string& addr) 
        : balance(0), address(addr) {}
    
    virtual ~Wallet() = default;
    
    // Pure virtual functions
    virtual bool send(double amount, const std::string& to) = 0;
    virtual void receive(double amount) = 0;
    
    // Common functionality
    double getBalance() const { return balance; }
    const std::string& getAddress() const { return address; }
    
    virtual void printTransactionHistory() const {
        std::cout << "Transaction History for " << address << ":\n";
        for (const auto& tx : transactionHistory) {
            std::cout << "- Amount: " << tx->getAmount() 
                      << " BTC, ID: " << tx->getId() << "\n";
        }
    }
};
```

### Step 2: Transaction Class

Create `transaction.h`:
```cpp
#pragma once
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class Transaction {
private:
    std::string id;
    double amount;
    std::string sender;
    std::string recipient;
    time_t timestamp;
    bool confirmed;

public:
    Transaction(const std::string& from, const std::string& to, double amt)
        : amount(amt), sender(from), recipient(to), 
          timestamp(std::time(nullptr)), confirmed(false) {
        // Generate simple transaction ID
        std::stringstream ss;
        ss << std::hex << timestamp << "_" << from.substr(0, 8);
        id = ss.str();
    }
    
    virtual ~Transaction() = default;
    
    // Getters
    const std::string& getId() const { return id; }
    double getAmount() const { return amount; }
    bool isConfirmed() const { return confirmed; }
    
    // Confirm transaction
    void confirm() { confirmed = true; }
    
    // String representation
    virtual std::string toString() const {
        std::stringstream ss;
        ss << "Transaction " << id << ":\n"
           << "  From: " << sender << "\n"
           << "  To: " << recipient << "\n"
           << "  Amount: " << amount << " BTC\n"
           << "  Status: " << (confirmed ? "Confirmed" : "Pending");
        return ss.str();
    }
};
```

### Step 3: Basic Wallet Implementation

Create `basic_wallet.h`:
```cpp
#pragma once
#include "wallet.h"
#include "transaction.h"

class BasicWallet : public Wallet {
public:
    BasicWallet(const std::string& addr) : Wallet(addr) {}
    
    bool send(double amount, const std::string& to) override {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        
        if (amount > balance) {
            throw std::runtime_error("Insufficient funds");
        }
        
        // Create and record transaction
        auto tx = std::make_shared<Transaction>(address, to, amount);
        balance -= amount;
        transactionHistory.push_back(tx);
        
        return true;
    }
    
    void receive(double amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        
        balance += amount;
        auto tx = std::make_shared<Transaction>("external", address, amount);
        tx->confirm();  // Incoming transactions are confirmed immediately
        transactionHistory.push_back(tx);
    }
};
```

### Step 4: Multi-Signature Wallet

Create `multisig_wallet.h`:
```cpp
#pragma once
#include "wallet.h"
#include <set>

class MultiSigWallet : public Wallet {
private:
    std::vector<std::string> signers;
    size_t requiredSignatures;
    std::set<std::string> pendingSignatures;

public:
    MultiSigWallet(const std::string& addr, 
                   const std::vector<std::string>& authorized,
                   size_t required)
        : Wallet(addr), signers(authorized), 
          requiredSignatures(required) {
        if (required > authorized.size()) {
            throw std::invalid_argument(
                "Required signatures cannot exceed number of signers"
            );
        }
    }
    
    bool send(double amount, const std::string& to) override {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        
        if (amount > balance) {
            throw std::runtime_error("Insufficient funds");
        }
        
        // In real implementation, would wait for signatures
        if (pendingSignatures.size() < requiredSignatures) {
            throw std::runtime_error(
                "Insufficient signatures for transaction"
            );
        }
        
        auto tx = std::make_shared<Transaction>(address, to, amount);
        balance -= amount;
        transactionHistory.push_back(tx);
        pendingSignatures.clear();
        
        return true;
    }
    
    void receive(double amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        
        balance += amount;
        auto tx = std::make_shared<Transaction>("external", address, amount);
        tx->confirm();
        transactionHistory.push_back(tx);
    }
    
    bool addSignature(const std::string& signer) {
        if (std::find(signers.begin(), signers.end(), signer) 
            == signers.end()) {
            return false;  // Not an authorized signer
        }
        
        pendingSignatures.insert(signer);
        return true;
    }
    
    size_t getSignatureCount() const {
        return pendingSignatures.size();
    }
    
    size_t getRequiredSignatures() const {
        return requiredSignatures;
    }
};
```

### Step 5: Watch-Only Wallet

Create `watch_wallet.h`:
```cpp
#pragma once
#include "wallet.h"

class WatchWallet : public Wallet {
public:
    WatchWallet(const std::string& addr) : Wallet(addr) {}
    
    bool send(double amount, const std::string& to) override {
        throw std::runtime_error(
            "Cannot send from watch-only wallet"
        );
    }
    
    void receive(double amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        
        // Only track balance, cannot actually receive
        balance += amount;
        auto tx = std::make_shared<Transaction>("external", address, amount);
        tx->confirm();
        transactionHistory.push_back(tx);
    }
};
```

### Step 6: Main Program

Create `main.cpp`:
```cpp
#include <iostream>
#include <memory>
#include "basic_wallet.h"
#include "multisig_wallet.h"
#include "watch_wallet.h"

void testWallet(std::shared_ptr<Wallet> wallet) {
    std::cout << "\nTesting wallet: " << wallet->getAddress() << "\n";
    std::cout << "Initial balance: " << wallet->getBalance() << " BTC\n";
    
    try {
        // Test receiving
        wallet->receive(1.5);
        std::cout << "Received 1.5 BTC\n";
        std::cout << "New balance: " << wallet->getBalance() << " BTC\n";
        
        // Test sending
        wallet->send(0.5, "recipient_address");
        std::cout << "Sent 0.5 BTC\n";
        std::cout << "Final balance: " << wallet->getBalance() << " BTC\n";
        
        // Print history
        wallet->printTransactionHistory();
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

int main() {
    try {
        // Create different wallet types
        auto basic = std::make_shared<BasicWallet>("basic_wallet_addr");
        
        auto multisig = std::make_shared<MultiSigWallet>(
            "multisig_wallet_addr",
            std::vector<std::string>{"signer1", "signer2", "signer3"},
            2  // Require 2 signatures
        );
        
        auto watch = std::make_shared<WatchWallet>("watch_wallet_addr");
        
        // Test each wallet type
        std::cout << "\n=== Testing Basic Wallet ===\n";
        testWallet(basic);
        
        std::cout << "\n=== Testing MultiSig Wallet ===\n";
        testWallet(multisig);
        
        std::cout << "\n=== Testing Watch-Only Wallet ===\n";
        testWallet(watch);
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
```

## Building and Running

1. Compile all files:
```bash
g++ -std=c++17 main.cpp -o wallet_system
```

2. Run the program:
```bash
./wallet_system
```

## Practice Exercises

1. Add more wallet types:
   - Hardware wallet simulation
   - Time-locked wallet
   - Multi-currency wallet

2. Enhance transaction handling:
   - Add transaction fees
   - Implement change addresses
   - Add transaction signing

3. Improve security:
   - Add basic encryption
   - Implement key derivation
   - Add address validation

## Common Issues and Solutions

### 1. Memory Management
```cpp
// Wrong: Raw pointer
Wallet* wallet = new BasicWallet("addr");

// Correct: Smart pointer
auto wallet = std::make_shared<BasicWallet>("addr");
```

### 2. Exception Safety
```cpp
// Wrong: No exception handling
wallet->send(amount, recipient);

// Correct: Handle exceptions
try {
    wallet->send(amount, recipient);
} catch (const std::exception& e) {
    // Handle error
}
```

### 3. Virtual Destructor
```cpp
// Wrong: Missing virtual destructor
class Wallet {
    ~Wallet() { }
};

// Correct:
class Wallet {
    virtual ~Wallet() = default;
};
```

## Knowledge Check

1. Why do we use pure virtual functions in the base wallet class?
2. How does polymorphism help in managing different wallet types?
3. Why use smart pointers for transactions?
4. How does exception handling improve wallet security?
5. What's the purpose of the watch-only wallet?

## Next Steps

1. **Enhance the System:**
   - Add persistent storage
   - Implement real cryptographic functions
   - Add network communication

2. **Learn More About:**
   - Bitcoin address formats
   - Transaction signing
   - Key management
   - Blockchain interaction

3. When you're ready, move on to [Pointers and Smart Pointers](../advanced/01_pointers.md)

Remember:
- Test all wallet operations thoroughly
- Handle errors appropriately
- Protect sensitive data
- Document your code
- Follow Bitcoin best practices