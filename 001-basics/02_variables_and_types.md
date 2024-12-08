# Variables and Data Types in C++

## Learning Objectives
- Understand what variables are and how to use them
- Learn basic data types and their uses
- Practice declaring and using variables
- See how data types are used in Bitcoin applications

## Prerequisites
- Basic understanding of programming concepts
- C++ development environment set up
- Familiarity with basic Bitcoin terms

## Concept Overview

### What is a Variable?
Think of a variable as a labeled box that holds a value. In Bitcoin development, we use variables to store everything from amounts to transaction data.

Basic variable examples:
```cpp
int myNumber = 42;        // A box labeled "myNumber" holding 42
double btcAmount = 0.5;   // A Bitcoin amount
bool isValid = true;      // Transaction validity flag
```

**Key Points:**
- Variables must be declared before use
- Each variable has a specific type
- Names should be descriptive

## Basic Data Types

### 1. Integers (Whole Numbers)
Used for whole number values in Bitcoin like block heights and confirmation counts.

```cpp
// Bitcoin-specific integer examples
int blockHeight = 750000;    // Current block number
int confirmations = 6;       // Number of confirmations
int64_t satoshis = 100000;  // Amount in satoshis

// Common integer operations
blockHeight++;               // Increment block height
confirmations *= 2;         // Double confirmations
```

**Key Points:**
- Use `int` for most whole numbers
- Use `int64_t` for large numbers (like satoshi amounts)
- Integers don't store decimal places

### 2. Decimal Numbers
Used for Bitcoin amounts and exchange rates.

```cpp
// Bitcoin-specific decimal examples
double bitcoinPrice = 45000.00;    // Price in USD
double btcAmount = 0.05;           // Amount in BTC
double fee = 0.0001;               // Transaction fee

// Common decimal operations
double total = btcAmount + fee;    // Calculate total with fee
```

**Key Points:**
- Use `double` for decimal numbers
- Be careful with precision in financial calculations
- Always validate decimal inputs

### 3. Boolean Values
Used for transaction validation and status flags.

```cpp
bool isValid = true;               // Transaction validity
bool hasEnoughFunds = false;       // Balance check
bool isTestnet = true;             // Network type

// Common boolean operations
bool canProceed = isValid && hasEnoughFunds;  // Logical AND
bool needsAttention = !isValid;               // Logical NOT
```

**Key Points:**
- Use for true/false conditions
- Common in validation checks
- Can be combined with logical operators

## Interactive Examples

### Example 1: Basic Variable Usage
Try modifying these values and observe the results:

<details>
<summary>👉 Click to see example</summary>

```cpp
#include <iostream>

int main() {
    // Declare and initialize variables
    int blockHeight = 750000;
    double btcAmount = 0.01;
    bool isValid = true;
    
    // Modify values
    blockHeight++;
    btcAmount *= 2;
    isValid = !isValid;
    
    // Display results
    std::cout << "Block Height: " << blockHeight << "\n";
    std::cout << "BTC Amount: " << btcAmount << "\n";
    std::cout << "Is Valid: " << std::boolalpha << isValid << "\n";
    
    return 0;
}
```
</details>

## Code-Along Exercises

### Exercise 1: Wallet Balance Manager
Create a program that manages a wallet's balance with different types of variables.

Requirements:
- Track balance in both BTC and satoshis
- Handle wallet status (active/inactive)
- Display formatted balances
- Implement basic validation

<details>
<summary>👉 Click to see step-by-step solution</summary>

```cpp
#include <iostream>
#include <iomanip>  // For setting decimal precision

int main() {
    // Step 1: Declare variables
    double btcBalance = 0.0;
    int64_t satoshiBalance = 0;
    bool isActive = true;
    
    // Step 2: Set initial values
    btcBalance = 0.05;  // 0.05 BTC
    satoshiBalance = btcBalance * 100000000;  // Convert to satoshis
    
    // Step 3: Display balances
    std::cout << std::fixed << std::setprecision(8);  // Set BTC precision
    std::cout << "BTC Balance: " << btcBalance << std::endl;
    std::cout << "Satoshi Balance: " << satoshiBalance << std::endl;
    std::cout << "Wallet Active: " << std::boolalpha << isActive << std::endl;
    
    return 0;
}
```

**Key Learning Points:**
- Using appropriate types for different values
- Converting between BTC and satoshis
- Formatting decimal output
- Using boolean flags
</details>

### Exercise 2: Transaction Calculator
Create a program that calculates transaction amounts and fees.

Requirements:
- Get transaction amount from user
- Calculate fee based on amount
- Validate input values
- Display formatted results

<details>
<summary>👉 Click to see step-by-step solution</summary>

```cpp
#include <iostream>
#include <iomanip>

int main() {
    // Step 1: Declare variables
    double transactionAmount;
    double feeRate = 0.0001;  // 0.01% fee
    double totalAmount;
    bool isValidAmount;
    
    // Step 2: Get transaction amount
    std::cout << "Enter BTC amount to send: ";
    std::cin >> transactionAmount;
    
    // Step 3: Validate and calculate
    isValidAmount = (transactionAmount > 0.0 && transactionAmount < 21000000.0);
    
    if (isValidAmount) {
        double fee = transactionAmount * feeRate;
        totalAmount = transactionAmount + fee;
        
        // Step 4: Display results
        std::cout << std::fixed << std::setprecision(8);
        std::cout << "Transaction amount: " << transactionAmount << " BTC\n";
        std::cout << "Fee: " << fee << " BTC\n";
        std::cout << "Total: " << totalAmount << " BTC\n";
    } else {
        std::cout << "Invalid amount entered!\n";
    }
    
    return 0;
}
```

**Key Learning Points:**
- Input validation
- Fee calculation
- Total amount computation
- Error handling with boolean flags
</details>

## Knowledge Check

1. **What's the difference between `int` and `double`?**
<details>
<summary>👉 Click to see answer</summary>

- `int`: Whole numbers only (e.g., 1, 2, 3)
- `double`: Decimal numbers (e.g., 1.5, 2.75)
- Example:
  ```cpp
  int whole = 5;      // Stores: 5
  double decimal = 5; // Stores: 5.0
  ```
</details>

2. **When should you use a `bool`?**
<details>
<summary>👉 Click to see answer</summary>

- For true/false conditions
- Examples: transaction validity, account status
- Common use cases:
  ```cpp
  bool isValid = true;
  bool hasEnoughFunds = balance >= amount;
  ```
</details>

3. **Why do we need different data types?**
<details>
<summary>👉 Click to see answer</summary>

- Different types store different kinds of data
- Memory efficiency (each type uses appropriate space)
- Type safety and error prevention
- Example:
  ```cpp
  int blockHeight = 750000;     // Whole number
  double amount = 0.05;         // Decimal
  bool isTestnet = false;       // True/false
  char network = 'm';          // Single character
  ```
</details>

## Practice Challenges

### Challenge 1: Multi-Currency Display (Beginner)
Create a program that displays Bitcoin amounts in multiple currencies.

Requirements:
- Store BTC amount
- Calculate USD equivalent (1 BTC = $45,000)
- Show both values formatted properly

<details>
<summary>👉 Click to see step-by-step solution</summary>

1. First, set up the variables:
```cpp
#include <iostream>
#include <iomanip>

int main() {
    double btcAmount = 0.5;
    double usdRate = 45000.0;
```

2. Calculate USD equivalent:
```cpp
    double usdAmount = btcAmount * usdRate;
```

3. Format and display results:
```cpp
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "BTC: " << btcAmount << std::endl;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "USD: $" << usdAmount << std::endl;
    
    return 0;
}
```

**Expected Output:**
```
BTC: 0.50000000
USD: $22500.00
```
</details>

### Challenge 2: Transaction History (Intermediate)
Create a program that tracks multiple transactions and calculates statistics.

Requirements:
- Track last 5 transactions
- Calculate running balance
- Show highest/lowest amounts

<details>
<summary>👉 Click to see step-by-step solution</summary>

1. Set up the basic structure:
```cpp
#include <iostream>
#include <array>
#include <algorithm>

int main() {
    std::array<double, 5> transactions = {0};
    double runningBalance = 0.0;
```

2. Add some transactions:
```cpp
    // Record transactions
    transactions[0] = 0.5;   // First deposit
    transactions[1] = -0.2;  // Withdrawal
    transactions[2] = 0.3;   // Another deposit
    transactions[3] = -0.1;  // Another withdrawal
    transactions[4] = 0.4;   // Final deposit
```

3. Calculate statistics:
```cpp
    // Update running balance
    for (double tx : transactions) {
        runningBalance += tx;
    }
    
    // Find highest and lowest
    double highest = *std::max_element(transactions.begin(), transactions.end());
    double lowest = *std::min_element(transactions.begin(), transactions.end());
```

4. Display results:
```cpp
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Final Balance: " << runningBalance << " BTC\n";
    std::cout << "Largest Transaction: " << highest << " BTC\n";
    std::cout << "Smallest Transaction: " << lowest << " BTC\n";
    
    return 0;
}
```

**Expected Output:**
```
Final Balance: 0.90000000 BTC
Largest Transaction: 0.50000000 BTC
Smallest Transaction: -0.20000000 BTC
```
</details>

## Common Mistakes

1. **Using Wrong Types**
```cpp
// Wrong - will lose decimal precision
int bitcoins = 0.5;  // Result: 0

// Correct - preserves decimal precision
double bitcoins = 0.5;  // Result: 0.5
```

2. **Integer Division**
```cpp
// Wrong - integer division truncates
int result = 5 / 2;  // Result: 2

// Correct - floating-point division
double result = 5.0 / 2.0;  // Result: 2.5
```

3. **Uninitialized Variables**
<details>
<summary>👉 Click to see explanation and solution</summary>

Problem: Using variables before giving them a value leads to undefined behavior.

```cpp
// Wrong - undefined behavior
double balance;
std::cout << balance;  // Could print anything!

// Correct - initialize before use
double balance = 0.0;
std::cout << balance;  // Always prints 0.0
```

Best practices:
- Always initialize variables when declaring them
- Use meaningful initial values
- Be especially careful with accumulator variables
</details>

## Next Steps
1. Practice with the provided exercises
2. Experiment with different data types
3. Move on to [Control Flow](03_control_flow.md)
4. Review Bitcoin Core examples of variable usage

## Additional Resources
- [C++ Data Types Reference](https://en.cppreference.com/w/cpp/language/types)
- [Bitcoin Core Source Examples](https://github.com/bitcoin/bitcoin)
- [Satoshi to BTC Converter](https://en.bitcoin.it/wiki/Units)