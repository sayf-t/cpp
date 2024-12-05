# STL Containers in Modern C++

## Learning Objectives
- Master STL container types and their use cases
- Understand container performance characteristics
- Learn container adaptors and algorithms
- Apply STL containers in Bitcoin Core development

## Prerequisites
- Understanding of templates
- Knowledge of iterators
- Familiarity with memory management
- Basic Bitcoin transaction concepts

## Introduction
The C++ Standard Template Library (STL) provides a rich set of container classes. In Bitcoin Core, these containers are crucial for managing transactions, blocks, and UTXO sets efficiently. We'll explore how to use them effectively in cryptocurrency applications.

## 1. Sequential Containers

### Vector
Most commonly used for dynamic arrays in Bitcoin Core:

```cpp
class Block {
public:
    void addTransaction(Transaction tx) {
        transactions_.push_back(std::move(tx));
    }
    
    size_t size() const { return transactions_.size(); }
    
    // Range-based for loop support
    auto begin() const { return transactions_.begin(); }
    auto end() const { return transactions_.end(); }
    
private:
    std::vector<Transaction> transactions_;
};
```

### Deque
Useful for block processing queues:

```cpp
class BlockProcessor {
public:
    void queueBlock(Block block) {
        pending_blocks_.push_back(std::move(block));
    }
    
    void processNext() {
        if (!pending_blocks_.empty()) {
            Block block = std::move(pending_blocks_.front());
            pending_blocks_.pop_front();
            processBlock(block);
        }
    }
    
private:
    std::deque<Block> pending_blocks_;
    void processBlock(const Block& block);
};
```

## 2. Associative Containers

### Unordered Map
Perfect for UTXO sets and transaction indexes:

```cpp
class UTXODatabase {
public:
    void addOutput(const OutPoint& outpoint, const TxOutput& output) {
        utxos_[outpoint] = output;
    }
    
    bool spendOutput(const OutPoint& outpoint) {
        return utxos_.erase(outpoint) > 0;
    }
    
    std::optional<TxOutput> getOutput(const OutPoint& outpoint) const {
        auto it = utxos_.find(outpoint);
        if (it != utxos_.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
private:
    std::unordered_map<OutPoint, TxOutput> utxos_;
};
```

### Set and Unordered Set
Useful for tracking unique elements like peer addresses:

```cpp
class PeerManager {
public:
    bool addPeer(const NetworkAddress& addr) {
        return known_peers_.insert(addr).second;
    }
    
    bool isKnownPeer(const NetworkAddress& addr) const {
        return known_peers_.contains(addr);
    }
    
private:
    std::unordered_set<NetworkAddress> known_peers_;
};
```

## 3. Container Adaptors

### Priority Queue
Essential for transaction fee prioritization:

```cpp
class MempoolManager {
public:
    void addTransaction(Transaction tx) {
        tx_queue_.push(std::move(tx));
    }
    
    Transaction getHighestFeeTx() {
        Transaction tx = std::move(tx_queue_.top());
        tx_queue_.pop();
        return tx;
    }
    
private:
    struct TxComparator {
        bool operator()(const Transaction& a, const Transaction& b) const {
            return a.getFeeRate() < b.getFeeRate();
        }
    };
    
    std::priority_queue<
        Transaction,
        std::vector<Transaction>,
        TxComparator
    > tx_queue_;
};
```

## 4. Advanced Container Usage

### Custom Allocators

```cpp
template<typename T>
class BlockchainAllocator {
public:
    using value_type = T;
    
    T* allocate(std::size_t n) {
        // Custom allocation strategy
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    
    void deallocate(T* p, std::size_t n) {
        ::operator delete(p);
    }
};

// Usage with containers
using BlockVector = std::vector<Block, BlockchainAllocator<Block>>;
```

### Container Performance Optimization

```cpp
class TransactionIndex {
public:
    void reserve(size_t size) {
        // Pre-allocate to avoid rehashing
        tx_index_.reserve(size);
    }
    
    void addTransaction(const std::string& txid, const Transaction& tx) {
        // Use emplace for in-place construction
        tx_index_.emplace(txid, tx);
    }
    
private:
    std::unordered_map<std::string, Transaction> tx_index_;
};
```

## 5. Bitcoin-Specific Container Examples

### Block Chain Storage

```cpp
class Blockchain {
public:
    void addBlock(Block block) {
        uint256 hash = block.getHash();
        
        // Store block
        blocks_.emplace(hash, std::move(block));
        
        // Update height index
        height_index_.emplace(current_height_++, hash);
    }
    
    Block* getBlockByHash(const uint256& hash) {
        auto it = blocks_.find(hash);
        return it != blocks_.end() ? &it->second : nullptr;
    }
    
    Block* getBlockByHeight(uint32_t height) {
        auto it = height_index_.find(height);
        if (it != height_index_.end()) {
            return getBlockByHash(it->second);
        }
        return nullptr;
    }
    
private:
    std::unordered_map<uint256, Block> blocks_;
    std::map<uint32_t, uint256> height_index_;
    uint32_t current_height_ = 0;
};
```

### Memory Pool Management

```cpp
class MemoryPool {
public:
    void addTransaction(Transaction tx) {
        const std::string& txid = tx.getTxid();
        
        // Store transaction
        transactions_.emplace(txid, std::move(tx));
        
        // Update fee index
        fee_index_.emplace(
            tx.getFeeRate(),
            txid
        );
    }
    
    std::vector<Transaction> getHighestFeeTxs(size_t n) {
        std::vector<Transaction> result;
        result.reserve(n);
        
        auto it = fee_index_.rbegin();
        while (result.size() < n && it != fee_index_.rend()) {
            auto tx_it = transactions_.find(it->second);
            if (tx_it != transactions_.end()) {
                result.push_back(tx_it->second);
            }
            ++it;
        }
        
        return result;
    }
    
private:
    std::unordered_map<std::string, Transaction> transactions_;
    std::multimap<double, std::string> fee_index_;
};
```

## Practice Exercises

1. **Basic Container Usage**
   - Implement a simple block chain using `std::vector`
   - Create a peer address manager using `std::set`
   - Build a transaction cache with `std::unordered_map`

2. **Advanced Containers**
   - Implement a memory pool with multiple indexes
   - Create a block processing queue with priorities
   - Build a UTXO cache with custom allocator

3. **Performance Optimization**
   - Optimize container memory usage
   - Implement efficient lookups
   - Create custom comparison functions

## Advanced Challenges

1. **Custom Containers**
   - Implement a specialized block storage container
   - Create a thread-safe transaction pool
   - Build a memory-efficient UTXO container

2. **Container Algorithms**
   - Implement block chain reorganization
   - Create efficient mempool ancestor tracking
   - Build transaction graph analysis tools

## Knowledge Check

1. Which container is best for storing ordered block heights?
2. How do you choose between `map` and `unordered_map`?
3. When should you use container adaptors?
4. What are the performance implications of different containers?

## Common Mistakes and Solutions

1. **Inefficient Container Choice**
   ```cpp
   // Wrong: Using vector for frequent lookups
   std::vector<Transaction> tx_pool;
   
   // Right: Using unordered_map for O(1) lookups
   std::unordered_map<std::string, Transaction> tx_pool;
   ```

2. **Missing Capacity Reservation**
   ```cpp
   // Wrong: No reservation
   std::vector<Block> blocks;
   for (int i = 0; i < 1000000; ++i) {
       blocks.push_back(block);  // Many reallocations
   }
   
   // Right: Reserve capacity
   std::vector<Block> blocks;
   blocks.reserve(1000000);
   for (int i = 0; i < 1000000; ++i) {
       blocks.push_back(block);  // Single allocation
   }
   ```

## Best Practices

1. Choose containers based on usage patterns
2. Reserve capacity when size is known
3. Use container adaptors for specific behaviors
4. Consider memory layout and cache efficiency
5. Profile container performance in real scenarios

## Next Steps
- Study STL algorithms
- Learn about parallel algorithms
- Explore custom allocators
- Practice with the UTXO Set project

## Additional Resources
- [C++ Containers Library](https://en.cppreference.com/w/cpp/container)
- [STL Algorithm Complexity](https://www.bigocheatsheet.com/)
- [Bitcoin Core Container Usage](https://github.com/bitcoin/bitcoin)