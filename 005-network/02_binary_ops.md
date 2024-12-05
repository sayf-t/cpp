# Binary Operations in C++

## Learning Objectives
- Master bitwise operations
- Understand binary data manipulation
- Learn Bitcoin's binary formats
- Implement efficient binary algorithms

## Prerequisites
- Understanding of serialization
- Basic C++ operators
- Knowledge of hexadecimal notation
- Familiarity with Bitcoin transactions

## Introduction
Binary operations are fundamental to Bitcoin Core development, from transaction hashing to script execution. We'll learn how to efficiently manipulate binary data while following Bitcoin protocol specifications.

## 1. Basic Binary Operations

### Bitwise Operators
```cpp
class BitcoinScript {
public:
    // Check if operation is disabled using flags
    bool isOperationEnabled(uint32_t flags, uint32_t operation) const {
        return (flags & operation) == operation;
    }
    
    // Combine script flags
    uint32_t combineFlags(uint32_t flag1, uint32_t flag2) {
        return flag1 | flag2;
    }
    
    // Remove specific flags
    uint32_t removeFlags(uint32_t currentFlags, uint32_t flagsToRemove) {
        return currentFlags & ~flagsToRemove;
    }
};

// Example usage with Bitcoin script flags
constexpr uint32_t SCRIPT_VERIFY_P2SH = (1U << 0);
constexpr uint32_t SCRIPT_VERIFY_STRICTENC = (1U << 1);
constexpr uint32_t SCRIPT_VERIFY_DERSIG = (1U << 2);
constexpr uint32_t SCRIPT_VERIFY_LOW_S = (1U << 3);
```

### Bit Manipulation
```cpp
class BitManipulator {
public:
    // Set specific bit
    static uint32_t setBit(uint32_t value, uint8_t position) {
        return value | (1U << position);
    }
    
    // Clear specific bit
    static uint32_t clearBit(uint32_t value, uint8_t position) {
        return value & ~(1U << position);
    }
    
    // Test specific bit
    static bool testBit(uint32_t value, uint8_t position) {
        return (value & (1U << position)) != 0;
    }
    
    // Count set bits (useful for script analysis)
    static uint8_t countSetBits(uint32_t value) {
        uint8_t count = 0;
        while (value) {
            count += value & 1;
            value >>= 1;
        }
        return count;
    }
};
```

## 2. Bitcoin-Specific Binary Operations

### Transaction Version Handling
```cpp
class TransactionVersion {
public:
    // Extract features from version
    static bool hasFeature(int32_t version, uint32_t feature) {
        return (version & feature) != 0;
    }
    
    // Add feature to version
    static int32_t addFeature(int32_t version, uint32_t feature) {
        return version | feature;
    }
    
    // Remove feature from version
    static int32_t removeFeature(int32_t version, uint32_t feature) {
        return version & ~feature;
    }
    
    // Check if version supports witness
    static bool supportsWitness(int32_t version) {
        return (version & WITNESS_FLAG) != 0;
    }

private:
    static constexpr uint32_t WITNESS_FLAG = (1U << 31);
};
```

### Script Operations
```cpp
class ScriptOperator {
public:
    // Implement basic script operations
    bool executeOp(uint8_t opcode, std::vector<std::vector<uint8_t>>& stack) {
        switch (opcode) {
            case OP_AND:
                return executeAND(stack);
            case OP_OR:
                return executeOR(stack);
            case OP_XOR:
                return executeXOR(stack);
            // ... other operations
        }
        return false;
    }
    
private:
    bool executeAND(std::vector<std::vector<uint8_t>>& stack) {
        if (stack.size() < 2) return false;
        
        auto b = stack.back(); stack.pop_back();
        auto a = stack.back(); stack.pop_back();
        
        std::vector<uint8_t> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] & b[i];
        }
        
        stack.push_back(result);
        return true;
    }
    
    bool executeOR(std::vector<std::vector<uint8_t>>& stack) {
        if (stack.size() < 2) return false;
        
        auto b = stack.back(); stack.pop_back();
        auto a = stack.back(); stack.pop_back();
        
        std::vector<uint8_t> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] | b[i];
        }
        
        stack.push_back(result);
        return true;
    }
    
    bool executeXOR(std::vector<std::vector<uint8_t>>& stack) {
        if (stack.size() < 2) return false;
        
        auto b = stack.back(); stack.pop_back();
        auto a = stack.back(); stack.pop_back();
        
        std::vector<uint8_t> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] ^ b[i];
        }
        
        stack.push_back(result);
        return true;
    }
};
```

## 3. Advanced Binary Techniques

### Compact Number Encoding
```cpp
class CompactInteger {
public:
    // Encode integer into compact form
    static std::vector<uint8_t> encode(uint64_t value) {
        std::vector<uint8_t> result;
        
        if (value <= 0xFC) {
            result.push_back(static_cast<uint8_t>(value));
        }
        else if (value <= 0xFFFF) {
            result.push_back(0xFD);
            result.push_back(value & 0xFF);
            result.push_back((value >> 8) & 0xFF);
        }
        else if (value <= 0xFFFFFFFF) {
            result.push_back(0xFE);
            for (int i = 0; i < 4; ++i) {
                result.push_back((value >> (8 * i)) & 0xFF);
            }
        }
        else {
            result.push_back(0xFF);
            for (int i = 0; i < 8; ++i) {
                result.push_back((value >> (8 * i)) & 0xFF);
            }
        }
        
        return result;
    }
    
    // Decode compact form back to integer
    static std::pair<uint64_t, size_t> decode(const uint8_t* data, size_t size) {
        if (size < 1) throw std::runtime_error("Invalid data size");
        
        uint8_t first = data[0];
        if (first <= 0xFC) {
            return {first, 1};
        }
        
        switch (first) {
            case 0xFD: {
                if (size < 3) throw std::runtime_error("Insufficient data");
                return {
                    (static_cast<uint64_t>(data[2]) << 8) |
                    static_cast<uint64_t>(data[1]),
                    3
                };
            }
            case 0xFE: {
                if (size < 5) throw std::runtime_error("Insufficient data");
                uint64_t value = 0;
                for (int i = 0; i < 4; ++i) {
                    value |= static_cast<uint64_t>(data[i + 1]) << (8 * i);
                }
                return {value, 5};
            }
            case 0xFF: {
                if (size < 9) throw std::runtime_error("Insufficient data");
                uint64_t value = 0;
                for (int i = 0; i < 8; ++i) {
                    value |= static_cast<uint64_t>(data[i + 1]) << (8 * i);
                }
                return {value, 9};
            }
            default:
                throw std::runtime_error("Invalid compact integer");
        }
    }
};
```

### Bit Field Operations
```cpp
class BloomFilter {
public:
    BloomFilter(size_t size, uint8_t numHashFuncs)
        : data_(size, 0)
        , numHashFuncs_(numHashFuncs) {}
    
    void insert(const std::vector<uint8_t>& element) {
        for (uint8_t i = 0; i < numHashFuncs_; ++i) {
            uint32_t hash = murmurHash3(element, i);
            setBit(hash % (data_.size() * 8));
        }
    }
    
    bool possiblyContains(const std::vector<uint8_t>& element) const {
        for (uint8_t i = 0; i < numHashFuncs_; ++i) {
            uint32_t hash = murmurHash3(element, i);
            if (!testBit(hash % (data_.size() * 8))) {
                return false;
            }
        }
        return true;
    }
    
private:
    std::vector<uint8_t> data_;
    uint8_t numHashFuncs_;
    
    void setBit(size_t index) {
        data_[index / 8] |= (1 << (index % 8));
    }
    
    bool testBit(size_t index) const {
        return (data_[index / 8] & (1 << (index % 8))) != 0;
    }
    
    static uint32_t murmurHash3(const std::vector<uint8_t>& data, uint32_t seed);
};
```

## Practice Exercises

1. **Basic Operations**
   - Implement a bit flag manager
   - Create a binary data parser
   - Build a script flag validator

2. **Bitcoin Protocol**
   - Implement VarInt encoding/decoding
   - Create transaction flag handling
   - Build script operation decoder

3. **Advanced Operations**
   - Implement a bloom filter
   - Create a merkle tree path verifier
   - Build a compact block filter

## Advanced Challenges

1. **Protocol Implementation**
   - Create a transaction witness handler
   - Implement segregated witness encoding
   - Build a script number calculator

2. **Optimization**
   - Optimize bloom filter operations
   - Implement fast binary search
   - Create efficient bit manipulation

## Knowledge Check

1. How do Bitcoin script flags work?
2. What is the purpose of compact integer encoding?
3. When should you use bitwise operations?
4. How do bloom filters use binary operations?

## Common Mistakes and Solutions

1. **Sign Extension**
   ```cpp
   // Wrong: Sign extension issues
   int32_t value = -1;
   uint32_t unsigned_value = value;  // All bits set!
   
   // Right: Explicit handling
   uint32_t unsigned_value = static_cast<uint32_t>(value);
   ```

2. **Bit Shifting**
   ```cpp
   // Wrong: Undefined behavior
   uint32_t value = 1;
   value = value << 32;  // UB!
   
   // Right: Range check
   uint32_t value = 1;
   if (shift < 32) {
       value = value << shift;
   }
   ```

## Best Practices

1. Use named constants for flags
2. Check bit operation ranges
3. Handle endianness consistently
4. Validate input data
5. Use appropriate integer types

## Next Steps
- Study Bitcoin transaction formats
- Learn about network message encoding
- Explore script execution
- Practice with Message Parser project

## Additional Resources
- [Bitcoin Script Wiki](https://en.bitcoin.it/wiki/Script)
- [Bitcoin Core Source](https://github.com/bitcoin/bitcoin/blob/master/src/script/script.h)
- [Protocol Documentation](https://developer.bitcoin.org/reference/transactions.html)