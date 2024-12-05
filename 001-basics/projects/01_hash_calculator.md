# Project 1: Building a Hash Calculator

Welcome to your first C++ project! We'll build a program that calculates cryptographic hashes, similar to those used in Bitcoin. This project combines everything you've learned so far.

## Learning Objectives
- Apply basic C++ concepts in a real project
- Understand cryptographic hashing
- Practice error handling
- Learn to use external libraries

## What is a Hash?

A hash is like a digital fingerprint. For example:
- Text: "Hello" → Hash: "185f8db32271fe25f561a6fc938b2e264306ec304eda518007d1764826381969"
- Every input produces a unique output
- You can't reverse a hash to get the original input

## Project Steps

### Step 1: Setup

First, install OpenSSL (we'll use it for hashing):

```bash
# For macOS
brew install openssl

# For Ubuntu/Debian
sudo apt-get install libssl-dev
```

### Step 2: Create Project Files

Create a new directory and file:
```bash
mkdir hash_calculator
cd hash_calculator
touch hash_calculator.cpp
```

### Step 3: Basic Implementation

Let's start with a simple version:

```cpp
// hash_calculator.cpp - Version 1
#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <iomanip>

// Function to convert bytes to hex string
std::string bytesToHex(const unsigned char* bytes, size_t length) {
    std::stringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < length; ++i) {
        hex_stream << std::setw(2) << static_cast<int>(bytes[i]);
    }
    
    return hex_stream.str();
}

// Function to calculate SHA-256 hash
std::string calculateHash(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);
    
    return bytesToHex(hash, SHA256_DIGEST_LENGTH);
}

int main() {
    std::string input;
    
    std::cout << "Simple Hash Calculator\n";
    std::cout << "Enter text to hash: ";
    std::getline(std::cin, input);
    
    std::string hash = calculateHash(input);
    std::cout << "SHA-256 Hash: " << hash << std::endl;
    
    return 0;
}
```

Compile and run:
```bash
# For macOS
g++ hash_calculator.cpp -o hash_calculator -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto

# For Linux
g++ hash_calculator.cpp -o hash_calculator -lssl -lcrypto
```

### Step 4: Adding Features

Let's enhance our program with more features:

```cpp
// hash_calculator.cpp - Version 2
#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <iomanip>
#include <stdexcept>

class HashCalculator {
private:
    // Helper function to convert bytes to hex
    static std::string bytesToHex(const unsigned char* bytes, size_t length) {
        std::stringstream hex_stream;
        hex_stream << std::hex << std::setfill('0');
        
        for (size_t i = 0; i < length; ++i) {
            hex_stream << std::setw(2) << static_cast<int>(bytes[i]);
        }
        
        return hex_stream.str();
    }

public:
    // Calculate single SHA-256 hash
    static std::string calculateHash(const std::string& input) {
        if (input.empty()) {
            throw std::invalid_argument("Input cannot be empty");
        }

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, input.c_str(), input.length());
        SHA256_Final(hash, &sha256);
        
        return bytesToHex(hash, SHA256_DIGEST_LENGTH);
    }
    
    // Calculate double SHA-256 (like Bitcoin)
    static std::string calculateDoubleHash(const std::string& input) {
        return calculateHash(calculateHash(input));
    }
};

void displayMenu() {
    std::cout << "\nHash Calculator Menu:\n";
    std::cout << "1. Calculate SHA-256\n";
    std::cout << "2. Calculate Double SHA-256 (Bitcoin-style)\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an option (1-3): ";
}

int main() {
    std::cout << "Welcome to Hash Calculator!\n";
    std::cout << "This program demonstrates hashing like in Bitcoin\n\n";
    
    while (true) {
        displayMenu();
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Clear newline
        
        if (choice == 3) {
            std::cout << "Goodbye!\n";
            break;
        }
        
        std::cout << "Enter text to hash: ";
        std::string input;
        std::getline(std::cin, input);
        
        try {
            std::string hash;
            switch (choice) {
                case 1:
                    hash = HashCalculator::calculateHash(input);
                    std::cout << "SHA-256: " << hash << std::endl;
                    break;
                    
                case 2:
                    hash = HashCalculator::calculateDoubleHash(input);
                    std::cout << "Double SHA-256: " << hash << std::endl;
                    std::cout << "(This is how Bitcoin calculates transaction IDs!)\n";
                    break;
                    
                default:
                    std::cout << "Invalid choice!\n";
                    continue;
            }
            
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}
```

### Step 5: Practice Exercises

1. Add file hashing:
```cpp
std::string calculateFileHash(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file");
    }
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    
    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        SHA256_Update(&sha256, buffer, file.gcount());
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);
    return bytesToHex(hash, SHA256_DIGEST_LENGTH);
}
```

2. Add hash verification:
```cpp
bool verifyHash(const std::string& input, const std::string& expectedHash) {
    std::string calculatedHash = calculateHash(input);
    return calculatedHash == expectedHash;
}
```

## Understanding Bitcoin Hashes

In Bitcoin:
1. Transaction IDs are double SHA-256 hashes of the transaction data
2. Blocks contain a Merkle root (a hash of all transaction hashes)
3. Mining involves finding a hash that starts with a certain number of zeros

Try hashing these Bitcoin-related strings:
```
"Hello, Bitcoin!"
"satoshi"
"Block #1"
```

## Common Issues and Solutions

### 1. OpenSSL Not Found
```bash
# Error: openssl/sha.h not found
# Solution: Install OpenSSL development files
```

### 2. Linking Errors
```bash
# Error: undefined reference to `SHA256_Init'
# Solution: Add -lssl -lcrypto to compilation command
```

### 3. Input Validation
```cpp
// Always check input
if (input.empty()) {
    throw std::invalid_argument("Input cannot be empty");
}
```

## Project Extensions

1. Add support for:
   - Different hash algorithms (SHA-1, RIPEMD160)
   - File hashing
   - Hash verification

2. Create a simple blockchain:
   - Hash previous block's data
   - Chain blocks together
   - Verify chain integrity

3. Implement a basic Merkle tree:
   - Hash pairs of transactions
   - Build tree structure
   - Generate Merkle root

## Knowledge Check

1. What is a cryptographic hash?
2. Why does Bitcoin use double SHA-256?
3. How do you convert bytes to hexadecimal?
4. Why is error handling important in cryptographic applications?
5. What is a Merkle tree used for in Bitcoin?

## Next Steps

1. **Experiment with:**
   - Different input types
   - Various hash algorithms
   - File hashing
   - Hash verification

2. **Learn More About:**
   - Bitcoin's use of hashing
   - Merkle trees
   - Blockchain structure
   - Mining and proof-of-work

3. When you're ready, move on to [Classes and Encapsulation](../oop/01_classes.md)

Remember:
- Test your program thoroughly
- Handle errors appropriately
- Document your code
- Understand the cryptographic concepts