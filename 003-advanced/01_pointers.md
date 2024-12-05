# Pointers and Smart Pointers in C++

## Learning Objectives
- Understand raw pointers and memory management
- Master modern C++ smart pointers
- Learn when to use different pointer types
- Apply pointer concepts to Bitcoin Core development

## Prerequisites
- Basic C++ syntax
- Understanding of memory and references
- Familiarity with classes and objects

## Introduction
In Bitcoin Core development, efficient memory management is crucial for handling blockchain data, transactions, and network messages. This tutorial will teach you how to use pointers and smart pointers effectively, with examples from cryptocurrency development.

## 1. Raw Pointers Basics

### What is a Pointer?
A pointer is a variable that stores the memory address of another variable. In Bitcoin Core, pointers are extensively used for managing dynamic data structures like transaction pools and block indexes.

```cpp
int main() {
    // Basic pointer example
    int blockHeight = 750000;
    int* pHeight = &blockHeight;  // pointer to blockHeight
    
    std::cout << "Block height: " << *pHeight << std::endl;  // Dereferencing
    
    // Dynamic allocation
    uint8_t* hashBuffer = new uint8_t[32];  // Typical size for Bitcoin hashes
    // ... use buffer ...
    delete[] hashBuffer;  // Manual cleanup required
}
```

### Common Pointer Operations
```cpp
class Transaction {
public:
    Transaction(double amount) : amount_(amount) {}
    double amount_;
};

int main() {
    // Creating pointers
    Transaction* tx = new Transaction(1.5);
    
    // Dereferencing
    double amount = (*tx).amount_;  // Or tx->amount_
    
    // Array of pointers
    Transaction* transactions[3];
    for(int i = 0; i < 3; i++) {
        transactions[i] = new Transaction(i * 1.0);
    }
    
    // Cleanup
    delete tx;
    for(int i = 0; i < 3; i++) {
        delete transactions[i];
    }
}
```

### Common Pitfalls
1. Memory Leaks
2. Dangling Pointers
3. Double Deletion
4. Null Pointer Dereferencing

## 2. Smart Pointers

Smart pointers are wrapper classes that manage memory automatically. Bitcoin Core uses them extensively to prevent memory leaks and ensure exception safety.

### unique_ptr
Used for exclusive ownership of a resource. Perfect for managing individual transactions or blocks.

```cpp
#include <memory>

class Block {
public:
    Block(int height) : height_(height) {}
    int height_;
};

int main() {
    // Creating a unique_ptr
    std::unique_ptr<Block> block = std::make_unique<Block>(750000);
    
    // Accessing members
    std::cout << "Block height: " << block->height_ << std::endl;
    
    // Automatic cleanup when block goes out of scope
}
```

### shared_ptr
Used when multiple objects need to share ownership. Useful for shared blockchain data.

```cpp
class Transaction {
public:
    Transaction(std::string txid) : txid_(txid) {}
    std::string txid_;
};

void processTransaction(std::shared_ptr<Transaction> tx) {
    // Process the transaction
    std::cout << "Processing tx: " << tx->txid_ << std::endl;
}

int main() {
    // Create a shared transaction
    auto tx = std::make_shared<Transaction>("abc123");
    
    // Multiple functions can share ownership
    processTransaction(tx);
    
    // Reference counting handles cleanup
}
```

### weak_ptr
Used to break circular references and observe shared objects without extending their lifetime.

```cpp
class Node {
public:
    Node(int data) : data_(data) {}
    std::weak_ptr<Node> next;  // Prevents circular reference in linked structures
    int data_;
};

int main() {
    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);
    
    node1->next = node2;  // Weak reference
    
    if (auto ptr = node1->next.lock()) {
        std::cout << "Node 2 data: " << ptr->data_ << std::endl;
    }
}
```

## 3. Bitcoin-Specific Examples

### Transaction Management
```cpp
class TransactionManager {
private:
    std::vector<std::unique_ptr<Transaction>> mempool_;
    std::shared_ptr<Block> currentBlock_;

public:
    void addToMempool(std::unique_ptr<Transaction> tx) {
        mempool_.push_back(std::move(tx));
    }
    
    void createBlock() {
        currentBlock_ = std::make_shared<Block>(750000);
        // Move transactions from mempool to block
    }
};
```

### UTXO Set Management
```cpp
class UTXO {
public:
    UTXO(std::string txid, int index) 
        : txid_(txid), index_(index) {}
    std::string txid_;
    int index_;
};

class UTXOSet {
private:
    std::unordered_map<std::string, std::shared_ptr<UTXO>> utxos_;

public:
    void addUTXO(std::string key, std::shared_ptr<UTXO> utxo) {
        utxos_[key] = utxo;
    }
};
```

## Practice Exercises

1. **Basic Pointer Manipulation**
   - Create a function that swaps two transaction amounts using pointers
   - Implement a simple linked list of blocks using raw pointers

2. **Smart Pointer Usage**
   - Convert the linked list to use smart pointers
   - Implement a transaction pool using `unique_ptr`
   - Create a block chain using `shared_ptr`

3. **Memory Management Challenge**
   - Implement a simple memory pool for transactions
   - Create a cache system using `weak_ptr`

## Knowledge Check

1. When should you use `unique_ptr` vs `shared_ptr`?
2. How do you prevent memory leaks when using raw pointers?
3. What are the advantages of smart pointers in Bitcoin Core development?
4. How can you safely share data between multiple objects?

## Common Mistakes and Solutions

1. **Memory Leaks**
   ```cpp
   // Wrong
   void processBlock(Block* block) {
       // No delete
   }
   
   // Right
   void processBlock(std::unique_ptr<Block> block) {
       // Automatic cleanup
   }
   ```

2. **Dangling Pointers**
   ```cpp
   // Wrong
   Block* getBlock() {
       Block b(1);
       return &b;  // Returns pointer to destroyed object
   }
   
   // Right
   std::unique_ptr<Block> getBlock() {
       return std::make_unique<Block>(1);
   }
   ```

## Next Steps
- Explore move semantics
- Learn about custom deleters
- Study Bitcoin Core's memory management patterns
- Practice with the Transaction Manager project

## Additional Resources
- [C++ Smart Pointers Documentation](https://en.cppreference.com/w/cpp/memory)
- [Bitcoin Core Source Code](https://github.com/bitcoin/bitcoin)
- Modern C++ Books and References
``` 