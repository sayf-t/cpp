# Variables and Data Types in C++

Welcome to your second C++ tutorial! Here you'll learn how to store and work with different types of data in your programs.

## Learning Objectives
- Understand what variables are and how to use them
- Learn basic data types and their uses
- Practice declaring and using variables
- See how data types are used in Bitcoin applications

## What is a Variable?

Think of a variable as a labeled box that holds a value:
```cpp
int myNumber = 42;        // A box labeled "myNumber" holding 42
```

## Basic Data Types

### 1. Integers (Whole Numbers)
```cpp
// Start with simple integers
int age = 25;             // Regular integer
int temperature = -10;    // Can be negative
int count = 0;           // Zero is valid too

// Bitcoin examples
int blockHeight = 750000; // Current block number in the blockchain
int confirmations = 6;    // Number of confirmations for a transaction
```

### 2. Decimal Numbers
```cpp
// Basic decimal numbers
double price = 10.99;     // Price in dollars
double height = 5.7;      // Height in feet

// Bitcoin examples
double bitcoinPrice = 45000.00;    // Price of 1 Bitcoin in USD
double btcAmount = 0.05;           // Amount of Bitcoin (1/20th of a BTC)
```

### 3. Single Characters
```cpp
char grade = 'A';         // Single character
char symbol = '$';        // Special character

// Bitcoin examples
char networkType = 'm';   // 'm' for mainnet, 't' for testnet
```

### 4. True/False Values
```cpp
bool isStudent = true;    // True or false
bool hasPassedTest = false;

// Bitcoin examples
bool isTestnet = false;   // Are we on the test network?
bool isValid = true;      // Is the transaction valid?
```

## Practice Program: Personal Wallet

Let's create a simple program that declares variables for a basic wallet:

```cpp
#include <iostream>

int main() {
    // Basic wallet information
    double bitcoinBalance = 0.05;        // Amount in BTC
    int satoshiBalance = 5000000;        // Same amount in satoshis
    bool isNewWallet = true;             // Is this a new wallet?
    char walletType = 'P';               // P for Personal

    // Display wallet information
    std::cout << "=== My First Bitcoin Wallet ===" << std::endl;
    std::cout << "Balance (BTC): " << bitcoinBalance << std::endl;
    std::cout << "Balance (satoshis): " << satoshiBalance << std::endl;
    std::cout << "New Wallet: " << std::boolalpha << isNewWallet << std::endl;
    std::cout << "Wallet Type: " << walletType << std::endl;

    return 0;
}
```

## Step-by-Step Exercises

### 1. Create a Temperature Converter
```cpp
#include <iostream>

int main() {
    // Declare variables
    double celsius = 25.0;
    double fahrenheit;

    // Convert celsius to fahrenheit
    fahrenheit = (celsius * 9.0/5.0) + 32.0;

    // Display results
    std::cout << celsius << "°C = " << fahrenheit << "°F" << std::endl;

    return 0;
}
```

### 2. Simple Transaction Calculator

Reference: [cout - cppreference.com](https://en.cppreference.com/w/cpp/io/cout)

```cpp
#include <iostream>

int main() {
    // Transaction details
    double btcAmount = 0.01;             // Amount to send
    int satoshisPerBTC = 100000000;      // Satoshis per Bitcoin
    int satoshiAmount;                   // Will store amount in satoshis
    bool hasSufficientFunds = true;      // Transaction validity check

    // Convert BTC to satoshis
    satoshiAmount = btcAmount * satoshisPerBTC;

    // Display information
    std::cout << "Transaction Amount (BTC): " << btcAmount << std::endl;
    std::cout << "Amount in satoshis: " << satoshiAmount << std::endl;
    std::cout << "Can proceed: " << std::boolalpha << hasSufficientFunds << std::endl;

    return 0;
}
```

## Common Mistakes and Solutions

### 1. Using Wrong Types
```cpp
// Wrong: Loss of precision
int bitcoins = 0.5;        // 0.5 will be truncated to 0!

// Correct: Use double for decimal numbers
double bitcoins = 0.5;     // Correctly stores 0.5
```

### 2. Integer Division
```cpp
// Wrong: Integer division
int result = 5 / 2;        // Result will be 2, not 2.5

// Correct: Use doubles for decimal division
double result = 5.0 / 2.0; // Result will be 2.5
```

### 3. Uninitialized Variables
```cpp
// Wrong: Variable not initialized
int balance;
std::cout << balance;      // Undefined behavior!

// Correct: Initialize before use
int balance = 0;
std::cout << balance;      // Prints 0
```

## Knowledge Check

Try to answer these questions:
1. What's the difference between `int` and `double`?
2. When should you use a `bool`?
3. Why do we need different data types?
4. How many satoshis are in one Bitcoin?
5. What happens if you try to store 0.5 in an `int`?

## Bitcoin-Specific Types (Preview)

As you advance, you'll work with these Bitcoin-specific types:
```cpp
// These will make more sense as you progress
uint32_t blockHeight = 750000;    // Unsigned 32-bit integer
int64_t satoshis = 100000000;     // 64-bit integer for amounts
uint8_t hash[32];                 // Array of bytes for hashes
```

## Practice Exercises

1. Create variables for a transaction:
   - Amount in BTC
   - Fee in satoshis
   - Transaction confirmation status
   - Number of confirmations

2. Create a simple balance checker:
   - Current balance
   - Pending transactions
   - Account status (active/inactive)

3. Build a coin converter:
   - Convert between BTC and satoshis
   - Convert between BTC and USD
   - Show different number formats

## Next Steps

1. **Experiment!** Try:
   - Different mathematical operations
   - Converting between types
   - Printing different formats

2. **Challenge Yourself:**
   - Create a more complex wallet program
   - Add transaction history variables
   - Calculate transaction fees

3. When you're comfortable with variables, move on to [Memory and References](03_memory_basics.md)

Remember:
- Always initialize your variables
- Choose appropriate types for your data
- Test your programs with different values
- Start simple and gradually add complexity