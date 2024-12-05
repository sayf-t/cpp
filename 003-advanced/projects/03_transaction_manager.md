# Project: Transaction Manager

In this project, we'll build a transaction manager that demonstrates advanced memory management concepts in C++. This project will help you understand how Bitcoin Core efficiently manages transactions in memory.

## Project Overview
We'll create a transaction management system that:
- Efficiently handles transaction memory allocation
- Uses smart pointers for automatic resource management
- Implements move semantics for optimal performance
- Manages a memory pool of transactions

## Learning Objectives
- Apply smart pointers in a real-world scenario
- Implement efficient move semantics
- Handle memory management in a thread-safe way
- Understand memory pool optimization

## Prerequisites
- Understanding of pointers and smart pointers
- Knowledge of move semantics
- Basic multithreading concepts
- STL container familiarity

## Project Structure

```cpp
src/
├── transaction.h
├── transaction.cpp
├── transaction_manager.h
├── transaction_manager.cpp
├── mempool.h
├── mempool.cpp
└── main.cpp
```

## Step 1: Transaction Class

```cpp
// transaction.h
#pragma once
#include <vector>
#include <string>
#include <memory>

class Transaction {
public:
    // Constructor with move semantics for data
    explicit Transaction(std::vector<uint8_t> data);
    
    // Move constructor and assignment
    Transaction(Transaction&& other) noexcept;
    Transaction& operator=(Transaction&& other) noexcept;
    
    // Delete copy operations to enforce move semantics
    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;
    
    // Getters
    const std::string& getTxid() const { return txid_; }
    size_t getSize() const { return data_.size(); }
    
private:
    std::vector<uint8_t> data_;
    std::string txid_;
    
    void calculateTxid();  // Compute transaction hash
};
```

```cpp
// transaction.cpp
#include "transaction.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

Transaction::Transaction(std::vector<uint8_t> data)
    : data_(std::move(data)) {
    calculateTxid();
}

Transaction::Transaction(Transaction&& other) noexcept
    : data_(std::move(other.data_))
    , txid_(std::move(other.txid_)) {}

Transaction& Transaction::operator=(Transaction&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        txid_ = std::move(other.txid_);
    }
    return *this;
}

void Transaction::calculateTxid() {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data_.data(), data_.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') 
           << static_cast<int>(hash[i]);
    }
    txid_ = ss.str();
}
```

## Step 2: Memory Pool Implementation

```cpp
// mempool.h
#pragma once
#include "transaction.h"
#include <unordered_map>
#include <mutex>
#include <optional>

class Mempool {
public:
    // Add transaction to pool (takes ownership)
    void addTransaction(std::unique_ptr<Transaction> tx);
    
    // Remove and return transaction
    std::unique_ptr<Transaction> removeTransaction(const std::string& txid);
    
    // Check if transaction exists
    bool hasTransaction(const std::string& txid) const;
    
    // Get total size of all transactions
    size_t getTotalSize() const;
    
private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::unique_ptr<Transaction>> transactions_;
    size_t totalSize_ = 0;
};
```

```cpp
// mempool.cpp
#include "mempool.h"

void Mempool::addTransaction(std::unique_ptr<Transaction> tx) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::string txid = tx->getTxid();
    totalSize_ += tx->getSize();
    transactions_[txid] = std::move(tx);
}

std::unique_ptr<Transaction> Mempool::removeTransaction(const std::string& txid) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = transactions_.find(txid);
    if (it == transactions_.end()) {
        return nullptr;
    }
    
    totalSize_ -= it->second->getSize();
    auto tx = std::move(it->second);
    transactions_.erase(it);
    return tx;
}

bool Mempool::hasTransaction(const std::string& txid) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return transactions_.find(txid) != transactions_.end();
}

size_t Mempool::getTotalSize() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return totalSize_;
}
```

## Step 3: Transaction Manager

```cpp
// transaction_manager.h
#pragma once
#include "mempool.h"
#include <vector>
#include <functional>

class TransactionManager {
public:
    // Add new transaction
    bool addTransaction(std::vector<uint8_t> txData);
    
    // Process transactions matching criteria
    void processTransactions(
        const std::function<bool(const Transaction&)>& predicate);
    
    // Get mempool statistics
    size_t getMempoolSize() const;
    size_t getTransactionCount() const;
    
private:
    Mempool mempool_;
};
```

```cpp
// transaction_manager.cpp
#include "transaction_manager.h"

bool TransactionManager::addTransaction(std::vector<uint8_t> txData) {
    try {
        auto tx = std::make_unique<Transaction>(std::move(txData));
        mempool_.addTransaction(std::move(tx));
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

void TransactionManager::processTransactions(
    const std::function<bool(const Transaction&)>& predicate) {
    // Implementation depends on specific requirements
    // Could involve removing transactions that match predicate
    // and processing them in some way
}

size_t TransactionManager::getMempoolSize() const {
    return mempool_.getTotalSize();
}

size_t TransactionManager::getTransactionCount() const {
    // Would need to add a method to Mempool to support this
    return 0;  // Placeholder
}
```

## Step 4: Main Program

```cpp
// main.cpp
#include "transaction_manager.h"
#include <iostream>
#include <random>

std::vector<uint8_t> generateRandomTransaction(size_t size) {
    std::vector<uint8_t> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    
    for (auto& byte : data) {
        byte = static_cast<uint8_t>(dis(gen));
    }
    return data;
}

int main() {
    TransactionManager txManager;
    
    // Add some random transactions
    for (int i = 0; i < 10; ++i) {
        auto txData = generateRandomTransaction(100);  // 100 bytes each
        if (txManager.addTransaction(std::move(txData))) {
            std::cout << "Added transaction " << i + 1 << std::endl;
        }
    }
    
    // Print statistics
    std::cout << "Mempool size: " << txManager.getMempoolSize() << " bytes\n";
    std::cout << "Transaction count: " << txManager.getTransactionCount() << "\n";
    
    return 0;
}
```

## Building and Running

1. Create a new directory for the project:
```bash
mkdir transaction_manager
cd transaction_manager
```

2. Create the source files with the code provided above.

3. Create a CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.10)
project(TransactionManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable(tx_manager
    src/main.cpp
    src/transaction.cpp
    src/mempool.cpp
    src/transaction_manager.cpp)

target_link_libraries(tx_manager OpenSSL::SSL OpenSSL::Crypto)
```

4. Build the project:
```bash
mkdir build
cd build
cmake ..
make
```

5. Run the program:
```bash
./tx_manager
```

## Practice Exercises

1. **Memory Pool Optimization**
   - Implement a size-based eviction policy
   - Add transaction prioritization
   - Implement memory usage limits

2. **Thread Safety**
   - Add concurrent transaction processing
   - Implement thread-safe transaction removal
   - Add deadlock prevention mechanisms

3. **Move Semantics**
   - Add batch transaction processing with move semantics
   - Implement efficient transaction reordering
   - Add transaction merging functionality

## Advanced Challenges

1. **Custom Memory Allocator**
   - Implement a custom allocator for transactions
   - Add memory pooling for small transactions
   - Implement memory defragmentation

2. **Performance Optimization**
   - Add transaction indexing
   - Implement parallel transaction validation
   - Add memory usage statistics

## Knowledge Check

1. How does move semantics improve the performance of transaction handling?
2. Why is thread safety important in the mempool implementation?
3. What are the benefits of using smart pointers in this project?
4. How does the transaction manager handle memory management?

## Next Steps

1. Add transaction validation
2. Implement transaction fee handling
3. Add persistence layer
4. Implement network communication

## Additional Resources
- [C++ Memory Model](https://en.cppreference.com/w/cpp/language/memory_model)
- [Smart Pointer Documentation](https://en.cppreference.com/w/cpp/memory)
- [Bitcoin Core Memory Pool](https://github.com/bitcoin/bitcoin/blob/master/src/txmempool.h)
``` 