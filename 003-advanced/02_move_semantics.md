# Move Semantics in Modern C++

## Learning Objectives
- Understand move semantics and rvalue references
- Master efficient resource transfer
- Learn when and how to implement move operations
- Apply move semantics in Bitcoin Core development

## Prerequisites
- Understanding of pointers and references
- Knowledge of smart pointers
- Basic class implementation experience

## Introduction
Move semantics is a crucial feature in modern C++ that enables efficient transfer of resources between objects. In Bitcoin Core development, it's extensively used for optimizing transaction and block handling, reducing unnecessary copies of large data structures.

## 1. Understanding Move Semantics

### What are Move Semantics?
Move semantics allow the transfer of resources from one object to another without copying. This is particularly important when dealing with large blockchain data structures.

```cpp
class Transaction {
public:
    // Constructor
    Transaction(std::vector<uint8_t> data) : data_(std::move(data)) {}
    
    // Move constructor
    Transaction(Transaction&& other) noexcept 
        : data_(std::move(other.data_)) {}
    
    // Move assignment operator
    Transaction& operator=(Transaction&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }

private:
    std::vector<uint8_t> data_;
};
```

### Rvalue References
Rvalue references (`&&`) are the foundation of move semantics:

```cpp
void processTransaction(Transaction&& tx) {
    // Process the moved transaction
}

int main() {
    Transaction tx(std::vector<uint8_t>{1, 2, 3});
    processTransaction(std::move(tx));  // tx is now in moved-from state
}
```

## 2. Move Semantics in Practice

### Moving Unique Resources
```cpp
class Block {
public:
    Block(std::vector<Transaction> txs) 
        : transactions_(std::move(txs)) {}
    
    // Move transaction into block
    void addTransaction(Transaction&& tx) {
        transactions_.push_back(std::move(tx));
    }

private:
    std::vector<Transaction> transactions_;
};
```

### Moving in STL Containers
```cpp
class Mempool {
public:
    void addTransaction(Transaction tx) {
        // Vector will move the transaction into place
        pending_transactions_.push_back(std::move(tx));
    }
    
    std::vector<Transaction> getTransactions() && {
        // Move entire vector when mempool is rvalue
        return std::move(pending_transactions_);
    }

private:
    std::vector<Transaction> pending_transactions_;
};
```

## 3. Bitcoin-Specific Examples

### Transaction Pool Management
```cpp
class TransactionPool {
public:
    // Add transaction with move semantics
    void addTransaction(Transaction&& tx) {
        std::string txid = tx.getId();
        pool_[txid] = std::move(tx);
    }
    
    // Remove and return transaction
    std::optional<Transaction> takeTransaction(const std::string& txid) {
        auto it = pool_.find(txid);
        if (it != pool_.end()) {
            Transaction tx = std::move(it->second);
            pool_.erase(it);
            return tx;
        }
        return std::nullopt;
    }

private:
    std::unordered_map<std::string, Transaction> pool_;
};
```

### Block Building
```cpp
class BlockBuilder {
public:
    BlockBuilder() = default;
    
    // Move transactions into block
    void addTransactions(std::vector<Transaction>&& txs) {
        transactions_ = std::move(txs);
    }
    
    // Build and return block, leaving builder empty
    Block build() && {
        return Block(std::move(transactions_));
    }

private:
    std::vector<Transaction> transactions_;
};
```

## 4. Performance Considerations

### When to Use Move Semantics
1. Large data transfers
2. Unique resource management
3. Container operations
4. Factory functions

### Move-Only Types
```cpp
class UTXOSet {
public:
    UTXOSet() = default;
    
    // Delete copy operations
    UTXOSet(const UTXOSet&) = delete;
    UTXOSet& operator=(const UTXOSet&) = delete;
    
    // Allow move operations
    UTXOSet(UTXOSet&&) noexcept = default;
    UTXOSet& operator=(UTXOSet&&) noexcept = default;

private:
    std::unordered_map<std::string, UTXO> utxos_;
};
```

## Practice Exercises

1. **Basic Move Operations**
   - Implement move constructor and assignment operator for a custom Transaction class
   - Create a move-only UTXO class

2. **Container Moves**
   - Build a transaction pool that efficiently moves transactions
   - Implement a block builder that moves transactions from mempool

3. **Advanced Move Semantics**
   - Create a custom memory pool with move semantics
   - Implement a chain reorganization function using move operations

## Knowledge Check

1. When should you use `std::move`?
2. What happens to an object after it's moved from?
3. How do move semantics improve performance?
4. What are the rules for noexcept move operations?

## Common Mistakes and Solutions

1. **Moving from const objects**
   ```cpp
   // Wrong
   const Transaction tx;
   auto moved_tx = std::move(tx);  // Still copies!
   
   // Right
   Transaction tx;
   auto moved_tx = std::move(tx);  // Actually moves
   ```

2. **Moving objects multiple times**
   ```cpp
   // Wrong
   Transaction tx;
   process(std::move(tx));
   process(std::move(tx));  // Undefined behavior!
   
   // Right
   Transaction tx1, tx2;
   process(std::move(tx1));
   process(std::move(tx2));
   ```

## Best Practices

1. Mark move operations as `noexcept`
2. Always leave moved-from objects in valid state
3. Check for self-assignment in move assignment
4. Use `std::move` at the point of transfer
5. Consider making resource-managing classes move-only

## Next Steps
- Study perfect forwarding
- Learn about return value optimization (RVO)
- Explore Bitcoin Core's move semantics usage
- Practice with the Transaction Manager project

## Additional Resources
- [C++ Move Semantics Documentation](https://en.cppreference.com/w/cpp/language/move_constructor)
- [Bitcoin Core Source Code](https://github.com/bitcoin/bitcoin)
- Modern C++ Move Semantics Articles 