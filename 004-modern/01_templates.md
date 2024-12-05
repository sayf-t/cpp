# Templates and Type Safety in Modern C++

## Learning Objectives
- Master C++ template programming
- Understand type safety mechanisms
- Learn template metaprogramming
- Apply templates to Bitcoin Core development

## Prerequisites
- Strong understanding of C++ basics
- Familiarity with OOP concepts
- Knowledge of memory management
- Basic understanding of Bitcoin transactions

## Introduction
Templates are a powerful feature in C++ that enable generic programming while maintaining type safety. In Bitcoin Core development, templates are extensively used for handling different transaction types, implementing consensus rules, and managing blockchain data structures.

## 1. Basic Template Concepts

### Function Templates
```cpp
// Generic hash function template
template<typename T>
std::string calculateHash(const T& data) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    
    // Use proper data access based on type
    if constexpr (std::is_same_v<T, std::vector<uint8_t>>) {
        SHA256_Update(&sha256, data.data(), data.size());
    } else {
        SHA256_Update(&sha256, &data, sizeof(T));
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);
    
    return BytesToHexString(hash, SHA256_DIGEST_LENGTH);
}

// Usage examples
std::vector<uint8_t> txData{1, 2, 3};
auto txHash = calculateHash(txData);

uint64_t blockHeight = 750000;
auto heightHash = calculateHash(blockHeight);
```

### Class Templates
```cpp
// Generic blockchain data structure
template<typename T>
class BlockchainData {
public:
    explicit BlockchainData(T data) : data_(std::move(data)) {}
    
    const T& getData() const { return data_; }
    std::string getHash() const { return calculateHash(data_); }
    
private:
    T data_;
};

// Specialization for transaction data
template<>
class BlockchainData<Transaction> {
public:
    explicit BlockchainData(Transaction tx) 
        : tx_(std::move(tx)) {}
    
    const Transaction& getData() const { return tx_; }
    std::string getHash() const { return tx_.getTxid(); }
    
private:
    Transaction tx_;
};
```

## 2. Advanced Template Features

### Template Type Deduction
```cpp
template<typename T>
class Amount {
public:
    explicit constexpr Amount(T value) : value_(value) {}
    
    constexpr T getValue() const { return value_; }
    
    // Automatic type deduction for arithmetic
    template<typename U>
    constexpr auto operator+(const Amount<U>& other) const {
        return Amount<decltype(value_ + other.getValue())>(
            value_ + other.getValue());
    }
    
private:
    T value_;
};

// Usage with Bitcoin amounts
Amount satoshis(100000000LL);  // 1 BTC in satoshis
Amount btc(1.0);               // 1 BTC as double
auto total = satoshis + btc;   // Type deduced automatically
```

### Variadic Templates
```cpp
// Merkle tree node builder
template<typename... Txs>
class MerkleNode {
public:
    static std::string calculateRoot(const Txs&... txs) {
        std::vector<std::string> hashes;
        (hashes.push_back(calculateHash(txs)), ...);
        return buildMerkleRoot(hashes);
    }
    
private:
    static std::string buildMerkleRoot(const std::vector<std::string>& hashes);
};
```

## 3. Type Safety Features

### Strong Types
```cpp
// Strong typing for different Bitcoin amounts
template<typename Tag>
class StrongAmount {
public:
    explicit constexpr StrongAmount(int64_t value) : value_(value) {}
    constexpr int64_t getValue() const { return value_; }
    
private:
    int64_t value_;
};

struct SatoshiTag {};
struct BTCTag {};

using Satoshi = StrongAmount<SatoshiTag>;
using BTC = StrongAmount<BTCTag>;

// Now these are different types
Satoshi sat(100000000);
BTC btc(1);
// sat = btc;  // Compilation error!
```

### Type Constraints
```cpp
// Ensure numeric types for amounts
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
class SafeAmount {
public:
    explicit SafeAmount(T value) : value_(value) {
        if (value < 0) throw std::invalid_argument("Negative amount");
    }
    
    T getValue() const { return value_; }
    
private:
    T value_;
};
```

## 4. Template Metaprogramming

### SFINAE and Type Traits
```cpp
// Enable different serialization based on type
template<typename T>
class Serializer {
public:
    template<typename U = T>
    std::enable_if_t<std::is_same_v<U, Transaction>, std::vector<uint8_t>>
    serialize(const T& data) {
        return serializeTransaction(data);
    }
    
    template<typename U = T>
    std::enable_if_t<std::is_same_v<U, Block>, std::vector<uint8_t>>
    serialize(const T& data) {
        return serializeBlock(data);
    }
    
private:
    static std::vector<uint8_t> serializeTransaction(const Transaction& tx);
    static std::vector<uint8_t> serializeBlock(const Block& block);
};
```

### Compile-Time Validation
```cpp
template<typename T>
class ScriptValidator {
    static_assert(std::is_base_of_v<Script, T>,
                 "Type must be derived from Script");
public:
    bool validate(const T& script) {
        if constexpr (std::is_same_v<T, P2PKHScript>) {
            return validateP2PKH(script);
        } else if constexpr (std::is_same_v<T, P2SHScript>) {
            return validateP2SH(script);
        }
        return false;
    }
};
```

## 5. Bitcoin-Specific Examples

### Generic UTXO Container
```cpp
template<typename Key, typename Value>
class UTXOSet {
public:
    void insert(const Key& key, Value&& value) {
        utxos_.insert({key, std::forward<Value>(value)});
    }
    
    template<typename Predicate>
    std::vector<Value> find_if(Predicate&& pred) {
        std::vector<Value> result;
        for (const auto& [key, value] : utxos_) {
            if (pred(key, value)) {
                result.push_back(value);
            }
        }
        return result;
    }
    
private:
    std::unordered_map<Key, Value> utxos_;
};
```

### Script Type System
```cpp
// Base template for all script types
template<typename OpCode>
class ScriptTemplate {
public:
    virtual bool execute(const std::vector<OpCode>& script) = 0;
    virtual ~ScriptTemplate() = default;
};

// Specialized P2PKH script
template<>
class ScriptTemplate<P2PKHOp> {
public:
    bool execute(const std::vector<P2PKHOp>& script) {
        // P2PKH-specific execution logic
        return validateSignature() && validatePubKey();
    }
    
private:
    bool validateSignature();
    bool validatePubKey();
};
```

## Practice Exercises

1. **Template Basics**
   - Create a template function for different hash algorithms
   - Implement a generic blockchain container
   - Build a type-safe amount calculator

2. **Advanced Templates**
   - Create a variadic template for script combination
   - Implement a compile-time script validator
   - Build a type-safe transaction builder

3. **Type Safety**
   - Implement strong types for different Bitcoin units
   - Create a template-based validation system
   - Build a type-safe serialization framework

## Advanced Challenges

1. **Template Metaprogramming**
   - Implement compile-time script analysis
   - Create a static transaction validator
   - Build a type-safe consensus rule checker

2. **Generic Programming**
   - Create a generic mempool container
   - Implement a template-based block builder
   - Design a type-safe signature checker

## Knowledge Check

1. When should you use class templates vs function templates?
2. How do type constraints improve code safety?
3. What are the benefits of strong typing in cryptocurrency code?
4. How can template metaprogramming prevent runtime errors?

## Common Mistakes and Solutions

1. **Template Code Bloat**
   ```cpp
   // Wrong: Unnecessary template
   template<typename T>
   void processTransaction(const T& tx) {
       // Same code for all types
   }
   
   // Right: Use concepts or type constraints
   template<typename T>
   requires TransactionLike<T>
   void processTransaction(const T& tx) {
       // Type-specific processing
   }
   ```

2. **Incorrect Type Constraints**
   ```cpp
   // Wrong: Too permissive
   template<typename T>
   void validateAmount(const T& amount) {
       // Unsafe for non-numeric types
   }
   
   // Right: Use type constraints
   template<Numeric T>
   void validateAmount(const T& amount) {
       // Safe for numeric types only
   }
   ```

## Best Practices

1. Use templates to avoid code duplication
2. Implement strong typing for domain-specific types
3. Use concepts to constrain template parameters
4. Leverage compile-time checks when possible
5. Document template requirements clearly

## Next Steps
- Study STL containers and algorithms
- Learn about template specialization
- Explore Bitcoin Core template usage
- Practice with the UTXO Set project

## Additional Resources
- [C++ Templates Documentation](https://en.cppreference.com/w/cpp/language/templates)
- [Modern C++ Design](https://www.amazon.com/Modern-Design-Generic-Programming-Patterns/dp/0201704315)
- [Bitcoin Core Template Usage](https://github.com/bitcoin/bitcoin)
``` 