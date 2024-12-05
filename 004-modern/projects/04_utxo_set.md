# Project: UTXO Set Implementation

In this project, we'll implement a high-performance UTXO (Unspent Transaction Output) set using modern C++ features. This is a critical component of any Bitcoin node, requiring efficient data structures and careful memory management.

## Project Overview
We'll create a UTXO set implementation that:
- Uses templates for generic coin handling
- Leverages STL containers for optimal performance
- Implements efficient memory management
- Provides thread-safe access methods

## Learning Objectives
- Apply template programming to cryptocurrency data structures
- Master STL container combinations
- Implement efficient caching mechanisms
- Handle concurrent UTXO access

## Prerequisites
- Understanding of templates and type safety
- Knowledge of STL containers
- Familiarity with Bitcoin transactions
- Experience with memory management

## Project Structure

```cpp
src/
├── utxo/
│   ├── types.h
│   ├── outpoint.h
│   ├── coin.h
│   ├── coin_view.h
│   ├── cache.h
│   └── set.h
├── utils/
│   ├── serializer.h
│   └── hasher.h
└── main.cpp
```

## Step 1: Core Types and Utilities

```cpp
// types.h
#pragma once
#include <cstdint>
#include <vector>
#include <array>

using Amount = int64_t;
using Hash256 = std::array<uint8_t, 32>;

// Custom hash function for Hash256
struct Hash256Hasher {
    size_t operator()(const Hash256& hash) const {
        // Use first 8 bytes for quick hash
        uint64_t value;
        std::memcpy(&value, hash.data(), sizeof(value));
        return value;
    }
};
```

```cpp
// outpoint.h
#pragma once
#include "types.h"
#include <functional>

class OutPoint {
public:
    OutPoint(Hash256 hash, uint32_t n) 
        : hash_(std::move(hash)), n_(n) {}
    
    const Hash256& getHash() const { return hash_; }
    uint32_t getN() const { return n_; }
    
    bool operator==(const OutPoint& other) const {
        return hash_ == other.hash_ && n_ == other.n_;
    }
    
private:
    Hash256 hash_;  // Transaction hash
    uint32_t n_;    // Output index
};

// Custom hash function for OutPoint
namespace std {
    template<>
    struct hash<OutPoint> {
        size_t operator()(const OutPoint& outpoint) const {
            size_t h1 = Hash256Hasher{}(outpoint.getHash());
            size_t h2 = std::hash<uint32_t>{}(outpoint.getN());
            return h1 ^ (h2 << 1);
        }
    };
}
```

## Step 2: Coin Implementation

```cpp
// coin.h
#pragma once
#include "types.h"
#include <memory>
#include <optional>

template<typename ScriptType>
class Coin {
public:
    Coin(Amount value, ScriptType script, uint32_t height)
        : value_(value)
        , script_(std::move(script))
        , height_(height)
        , is_coinbase_(false) {}
    
    // Getters
    Amount getValue() const { return value_; }
    const ScriptType& getScript() const { return script_; }
    uint32_t getHeight() const { return height_; }
    bool isCoinbase() const { return is_coinbase_; }
    
    // Serialization
    std::vector<uint8_t> serialize() const;
    static std::optional<Coin> deserialize(const std::vector<uint8_t>& data);
    
private:
    Amount value_;
    ScriptType script_;
    uint32_t height_;
    bool is_coinbase_;
};
```

## Step 3: UTXO Cache Implementation

```cpp
// cache.h
#pragma once
#include "coin.h"
#include "outpoint.h"
#include <unordered_map>
#include <shared_mutex>

template<typename ScriptType>
class UTXOCache {
public:
    using CoinType = Coin<ScriptType>;
    
    // Thread-safe coin access
    std::optional<CoinType> getCoin(const OutPoint& outpoint) const {
        std::shared_lock lock(mutex_);
        auto it = cache_.find(outpoint);
        if (it != cache_.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    // Add coin to cache
    void addCoin(const OutPoint& outpoint, CoinType&& coin) {
        std::unique_lock lock(mutex_);
        cache_.emplace(outpoint, std::move(coin));
    }
    
    // Remove coin from cache
    bool removeCoin(const OutPoint& outpoint) {
        std::unique_lock lock(mutex_);
        return cache_.erase(outpoint) > 0;
    }
    
    // Batch updates
    template<typename InputIt>
    void batchUpdate(InputIt first, InputIt last) {
        std::unique_lock lock(mutex_);
        for (auto it = first; it != last; ++it) {
            const auto& [outpoint, coin] = *it;
            if (coin) {
                cache_.insert_or_assign(outpoint, std::move(*coin));
            } else {
                cache_.erase(outpoint);
            }
        }
    }
    
private:
    mutable std::shared_mutex mutex_;
    std::unordered_map<OutPoint, CoinType> cache_;
};
```

## Step 4: UTXO Set Implementation

```cpp
// set.h
#pragma once
#include "cache.h"
#include <memory>
#include <vector>

template<typename ScriptType>
class UTXOSet {
public:
    using CoinType = Coin<ScriptType>;
    using CacheType = UTXOCache<ScriptType>;
    
    // Constructor with custom cache size
    explicit UTXOSet(size_t cache_size = 100000)
        : cache_(std::make_unique<CacheType>()) {
        // Initialize cache with size hint
    }
    
    // Get coin with caching
    std::optional<CoinType> getCoin(const OutPoint& outpoint) const {
        // Try cache first
        if (auto coin = cache_->getCoin(outpoint)) {
            return coin;
        }
        
        // Try database
        if (auto coin = fetchFromDatabase(outpoint)) {
            cache_->addCoin(outpoint, *coin);
            return coin;
        }
        
        return std::nullopt;
    }
    
    // Apply new block
    void applyBlock(const Block& block) {
        std::vector<std::pair<OutPoint, std::optional<CoinType>>> updates;
        updates.reserve(block.getTotalIO());
        
        // Remove spent outputs
        for (const auto& tx : block.getTransactions()) {
            for (const auto& input : tx.getInputs()) {
                updates.emplace_back(input.getOutPoint(), std::nullopt);
            }
        }
        
        // Add new outputs
        uint32_t height = block.getHeight();
        for (const auto& tx : block.getTransactions()) {
            for (size_t n = 0; n < tx.getOutputs().size(); ++n) {
                const auto& output = tx.getOutputs()[n];
                updates.emplace_back(
                    OutPoint(tx.getHash(), n),
                    CoinType(output.getValue(), output.getScript(), height)
                );
            }
        }
        
        // Batch update cache
        cache_->batchUpdate(updates.begin(), updates.end());
        
        // Update database
        updateDatabase(updates);
    }
    
    // Statistics
    size_t getCacheSize() const {
        return cache_->size();
    }
    
private:
    std::unique_ptr<CacheType> cache_;
    
    // Database operations
    std::optional<CoinType> fetchFromDatabase(const OutPoint& outpoint) const;
    void updateDatabase(const std::vector<std::pair<OutPoint, std::optional<CoinType>>>& updates);
};
```

## Step 5: Main Program

```cpp
// main.cpp
#include "utxo/set.h"
#include <iostream>

// Example script type
struct P2PKHScript {
    std::vector<uint8_t> pubKeyHash;
    bool operator==(const P2PKHScript& other) const {
        return pubKeyHash == other.pubKeyHash;
    }
};

int main() {
    // Create UTXO set with P2PKH scripts
    UTXOSet<P2PKHScript> utxoSet;
    
    // Create some test coins
    Hash256 txHash{/* ... */};
    OutPoint out1(txHash, 0);
    P2PKHScript script{/* ... */};
    
    // Add coin
    Coin<P2PKHScript> coin(50000000, script, 100);
    utxoSet.addCoin(out1, std::move(coin));
    
    // Query coin
    if (auto found = utxoSet.getCoin(out1)) {
        std::cout << "Found coin with value: " << found->getValue() << "\n";
    }
    
    return 0;
}
```

## Building and Running

1. Create project directory:
```bash
mkdir utxo_set
cd utxo_set
```

2. Create CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.14)
project(UTXOSet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(utxo_set
    src/main.cpp)

target_include_directories(utxo_set PRIVATE src)
```

3. Build:
```bash
mkdir build
cd build
cmake ..
make
```

4. Run:
```bash
./utxo_set
```

## Practice Exercises

1. **Basic Operations**
   - Implement coin serialization
   - Add merkle tree verification
   - Create basic database backend

2. **Performance Optimization**
   - Implement LRU cache eviction
   - Add bloom filter for quick lookups
   - Optimize memory usage

3. **Advanced Features**
   - Add support for different script types
   - Implement atomic batch updates
   - Create snapshot functionality

## Advanced Challenges

1. **Scaling Solutions**
   - Implement pruning mechanism
   - Add parallel validation
   - Create efficient index structures

2. **Database Integration**
   - Add persistent storage
   - Implement crash recovery
   - Create backup functionality

## Knowledge Check

1. How does the template design improve code reusability?
2. Why is thread safety important in UTXO management?
3. What are the benefits of the caching system?
4. How does the batch update improve performance?

## Next Steps

1. Add more script types
2. Implement database backend
3. Add network synchronization
4. Create visualization tools

## Additional Resources
- [Bitcoin Core UTXO Set](https://github.com/bitcoin/bitcoin/blob/master/src/coins.h)
- [UTXO Set Optimizations](https://github.com/bitcoin/bitcoin/blob/master/doc/design/utxo_set.md)
- [Bitcoin Developer Guide](https://developer.bitcoin.org/devguide/transactions.html)