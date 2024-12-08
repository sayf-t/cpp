# Control Flow in C++

## Learning Objectives
- Master conditional statements (if, switch)
- Understand different types of loops
- Learn when to use each control structure
- Apply control flow to Bitcoin scenarios

## Prerequisites
- Understanding of variables and data types
- Basic C++ syntax knowledge
- Development environment set up

## Core Concepts

### 1. Conditional Statements
Control flow determines how your program makes decisions. In Bitcoin development, we use conditionals for transaction validation, balance checks, and network status.

#### If Statements
Basic decision making:
```cpp
if (balance >= amount) {
    // Can make transaction
    processTransaction();
} else {
    // Insufficient funds
    displayError();
}
```

Multiple conditions:
```cpp
if (amount <= 0) {
    std::cout << "Invalid amount\n";
} else if (amount > balance) {
    std::cout << "Insufficient funds\n";
} else if (amount > maxLimit) {
    std::cout << "Exceeds limit\n";
} else {
    std::cout << "Transaction valid\n";
}
```

#### Switch Statements
Used for multiple exact value matches:
```cpp
switch (transactionType) {
    case 'S':  // Send
        processSend();
        break;
    case 'R':  // Receive
        processReceive();
        break;
    case 'P':  // Payment
        processPayment();
        break;
    default:
        handleUnknown();
        break;
}
```

### 2. Loops
Loops are used for repetitive tasks like processing multiple transactions or waiting for confirmations.

#### While Loop
```cpp
int confirmations = 0;
while (confirmations < 6) {
    if (newBlockFound()) {
        confirmations++;
    }
    waitForNextBlock();
}
```

#### Do-While Loop
```cpp
double amount;
do {
    std::cout << "Enter valid amount (>0): ";
    std::cin >> amount;
} while (amount <= 0);
```

#### For Loop
```cpp
// Process last 10 transactions
for (int i = 0; i < 10; i++) {
    processTransaction(transactions[i]);
}
```

## Interactive Examples

### Example 1: Basic Transaction Validation
Try this example to understand conditional statements:

<details>
<summary>👉 Click to see example</summary>

```cpp
#include <iostream>

int main() {
    double balance = 1.5;
    double amount = 2.0;
    
    // Basic validation
    if (amount <= 0) {
        std::cout << "Invalid amount\n";
    } else if (amount > balance) {
        std::cout << "Insufficient funds\n";
    } else {
        std::cout << "Transaction valid\n";
        balance -= amount;
    }
    
    return 0;
}
```

**Key Points:**
- Condition order matters
- Each condition is checked in sequence
- Only one block executes
</details>

## Code-Along Exercises

### Exercise 1: Transaction Validator
Build a program that validates Bitcoin transactions using various conditions.

Requirements:
- Check transaction amount
- Verify sufficient balance
- Validate confirmation count
- Handle different transaction types

<details>
<summary>👉 Click to see step-by-step solution</summary>

1. Set up the basic structure:
```cpp
#include <iostream>

int main() {
    double amount, balance;
    int confirmations;
    char txType;
```

2. Get transaction details:
```cpp
    std::cout << "Enter amount: ";
    std::cin >> amount;
    std::cout << "Current balance: ";
    std::cin >> balance;
    std::cout << "Confirmations: ";
    std::cin >> confirmations;
    std::cout << "Transaction type (S/R/P): ";
    std::cin >> txType;
```

3. Implement validation:
```cpp
    // Amount validation
    if (amount <= 0) {
        std::cout << "Error: Invalid amount\n";
        return 1;
    }
    
    // Balance check
    if (amount > balance) {
        std::cout << "Error: Insufficient funds\n";
        return 1;
    }
    
    // Confirmation check
    if (confirmations < 6) {
        std::cout << "Warning: Waiting for confirmations\n";
    }
```

4. Process transaction type:
```cpp
    switch (toupper(txType)) {
        case 'S':
            std::cout << "Processing send...\n";
            break;
        case 'R':
            std::cout << "Processing receive...\n";
            break;
        case 'P':
            std::cout << "Processing payment...\n";
            break;
        default:
            std::cout << "Error: Invalid transaction type\n";
            return 1;
    }
    
    std::cout << "Transaction validated successfully!\n";
    return 0;
}
```
</details>

### Exercise 2: Block Confirmation Monitor
Create a program that monitors block confirmations using loops.

Requirements:
- Track confirmation count
- Handle chain reorganization
- Allow user interaction
- Display status updates

<details>
<summary>👉 Click to see step-by-step solution</summary>

// ... solution content ...
</details>

## Knowledge Check

1. **When should you use a switch instead of if-else chains?**
<details>
<summary>👉 Click to see answer</summary>

- Use switch when:
  - Testing a single variable against multiple exact values
  - You have many (3+) conditions on the same variable
  - You want better readability
- Example:
  ```cpp
  // Better as switch
  switch (txType) {
      case 'S': handleSend(); break;
      case 'R': handleReceive(); break;
      case 'P': handlePayment(); break;
      default: handleUnknown(); break;
  }
  ```
</details>

2. **What's the difference between while and do-while loops?**
<details>
<summary>👉 Click to see answer</summary>

- while loop: checks condition before executing
- do-while loop: executes at least once, then checks condition
- Example:
  ```cpp
  // while loop might never execute
  while (balance < 0) {
      requestDeposit();
  }

  // do-while always executes at least once
  do {
      processTransaction();
  } while (hasMoreTransactions());
  ```
Best use cases:
- Use while for: pre-condition checking
- Use do-while for: input validation, menu systems
</details>

3. **Why use break in a switch statement?**
<details>
<summary>👉 Click to see answer</summary>

- Prevents fall-through to next case
- Ensures each case executes independently
- Example of what happens without break:
  ```cpp
  switch (txStatus) {
      case 'P':  // Pending
          cout << "Pending";
          // No break! Falls through to next case
      case 'C':  // Confirmed
          cout << "Confirmed";
  }
  // Output if txStatus is 'P': "PendingConfirmed"
  ```
</details>

4. **When should you use continue in a loop?**
<details>
<summary>👉 Click to see answer</summary>

- To skip remaining loop body for current iteration
- When early iteration termination is needed
- Example:
  ```cpp
  for (const auto& tx : transactions) {
      if (!tx.isValid()) {
          continue;  // Skip invalid transactions
      }
      processTransaction(tx);
  }
  ```
</details>

5. **What's the difference between = and == in conditions?**
<details>
<summary>👉 Click to see answer</summary>

- = is assignment (sets a value)
- == is comparison (checks equality)
- Common bug example:
  ```cpp
  // Bug: Always true because it assigns 100
  if (value = 100) {
      cout << "Value is 100\n";
  }

  // Correct: Compares value to 100
  if (value == 100) {
      cout << "Value is 100\n";
  }
  ```
</details>

### Challenge 2: Block Confirmation Counter (Intermediate)
Create a program that tracks block confirmations with chain reorganization handling.

Requirements:
- Start with confirmations = 0
- Allow user to:
  - Add new block ('n')
  - Remove last confirmation ('r') for chain reorg
  - Quit checking ('q')
- Keep track of confirmations (minimum 0)
- Print "Transaction Confirmed!" when confirmations reach 6

<details>
<summary>👉 Click to see step-by-step solution</summary>

1. Set up the program structure:
```cpp
#include <iostream>

int main() {
    int confirmations = 0;
    char action;
```

2. Create the main loop:
```cpp
    do {
        // Display current status
        std::cout << "\nCurrent confirmations: " << confirmations;
        if (confirmations >= 6) {
            std::cout << " (Confirmed!)";
        }
        std::cout << "\nActions: [n]ew block, [r]eorg, [q]uit\n";
        std::cout << "Choose action: ";
        std::cin >> action;
```

3. Implement action handling:
```cpp
        switch (std::tolower(action)) {
            case 'n':  // New block
                confirmations++;
                std::cout << "Block added.\n";
                break;
                
            case 'r':  // Chain reorg
                if (confirmations > 0) {
                    confirmations--;
                    std::cout << "Removed last confirmation.\n";
                } else {
                    std::cout << "No confirmations to remove.\n";
                }
                break;
                
            case 'q':  // Quit
                std::cout << "Exiting...\n";
                break;
                
            default:
                std::cout << "Invalid action!\n";
        }
```

4. Add confirmation check:
```cpp
        // Check if newly confirmed
        if (confirmations == 6) {
            std::cout << "\n🎉 Transaction confirmed! 🎉\n";
        }
    } while (std::tolower(action) != 'q');
    
    return 0;
}
```

**Expected Output:**
```
Current confirmations: 0
Actions: [n]ew block, [r]eorg, [q]uit
Choose action: n
Block added.

Current confirmations: 1
Actions: [n]ew block, [r]eorg, [q]uit
Choose action: n
Block added.
...
Current confirmations: 6 (Confirmed!)
🎉 Transaction confirmed! 🎉
```
</details>

### Challenge 3: Transaction Batch Processor (Advanced)
Create a program that processes multiple transactions with validation.

Requirements:
- Ask user how many transactions to process
- For each transaction:
  - Get amount and fee
  - Validate inputs (no negative values)
  - Skip invalid transactions
  - Track total amount and fees
- Print summary at end

<details>
<summary>👉 Click to see step-by-step solution</summary>

1. Set up the basic structure:
```cpp
#include <iostream>
#include <iomanip>
#include <vector>

struct Transaction {
    double amount;
    double fee;
    bool isValid;
};
```

2. Implement validation function:
```cpp
bool validateTransaction(double amount, double fee) {
    if (amount <= 0) return false;
    if (fee < 0) return false;
    if (fee > amount * 0.1) return false;  // Max 10% fee
    return true;
}
```

3. Create the main program:
```cpp
int main() {
    int numTransactions;
    std::vector<Transaction> transactions;
    
    // Get number of transactions
    std::cout << "Enter number of transactions to process: ";
    std::cin >> numTransactions;
    
    if (numTransactions <= 0) {
        std::cout << "Invalid number of transactions!\n";
        return 1;
    }
```

4. Process transactions:
```cpp
    // Process each transaction
    for (int i = 0; i < numTransactions; i++) {
        Transaction tx;
        
        std::cout << "\nTransaction " << (i + 1) << ":\n";
        std::cout << "Amount (BTC): ";
        std::cin >> tx.amount;
        std::cout << "Fee (BTC): ";
        std::cin >> tx.fee;
        
        tx.isValid = validateTransaction(tx.amount, tx.fee);
        
        if (!tx.isValid) {
            std::cout << "Invalid transaction, skipping!\n";
        }
        
        transactions.push_back(tx);
    }
```

5. Generate and display summary:
```cpp
    // Calculate totals
    double totalAmount = 0, totalFees = 0;
    int validCount = 0;
    
    for (const auto& tx : transactions) {
        if (tx.isValid) {
            totalAmount += tx.amount;
            totalFees += tx.fee;
            validCount++;
        }
    }
    
    // Display summary
    std::cout << "\nTransaction Summary:\n";
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Valid Transactions: " << validCount << "/" 
              << transactions.size() << "\n";
    std::cout << "Total Amount: " << totalAmount << " BTC\n";
    std::cout << "Total Fees: " << totalFees << " BTC\n";
    std::cout << "Net Amount: " << (totalAmount - totalFees) << " BTC\n";
    
    return 0;
}
```

**Expected Output:**
```
Enter number of transactions to process: 3

Transaction 1:
Amount (BTC): 0.5
Fee (BTC): 0.001

Transaction 2:
Amount (BTC): -1
Fee (BTC): 0.001
Invalid transaction, skipping!

Transaction 3:
Amount (BTC): 0.3
Fee (BTC): 0.0005

Transaction Summary:
Valid Transactions: 2/3
Total Amount: 0.80000000 BTC
Total Fees: 0.00150000 BTC
Net Amount: 0.79850000 BTC
```
</details>

## Common Mistakes

1. **Missing break in switch**
```cpp
// Wrong - falls through cases
switch (type) {
    case 'A': cout << "A";    // Falls through to B!
    case 'B': cout << "B";
}

// Correct - uses break
switch (type) {
    case 'A': cout << "A"; break;
    case 'B': cout << "B"; break;
}
```

2. **Infinite Loops**
<details>
<summary>👉 Click to see explanation and solution</summary>

Problem: Loop condition never becomes false

```cpp
// Wrong - infinite loop
while (balance > 0) {
    cout << balance;  // Never changes balance
}

// Correct - modifies condition variable
while (balance > 0) {
    cout << balance;
    balance -= 0.1;
}
```

Best practices:
- Always modify loop control variable
- Include clear exit condition
- Consider using for loop when iteration count is known
</details>

3. **Assignment in Conditions**
<details>
<summary>👉 Click to see explanation and solution</summary>

Problem: Using = (assignment) instead of == (comparison)

```cpp
// Wrong - always true
if (value = 100) {  // Assigns 100 to value
    cout << "Equal\n";
}

// Correct - compares value to 100
if (value == 100) {
    cout << "Equal\n";
}
```

Best practices:
- Use compiler warnings
- Consider using constants on left side: `if (100 == value)`
- Review code carefully for this common mistake
</details>

## Next Steps
1. Practice with the provided exercises
2. Experiment with different control structures
3. Move on to [Memory Management](04_memory_basics.md)
4. Study Bitcoin Core control flow examples

## Additional Resources
- [C++ Control Flow Reference](https://en.cppreference.com/w/cpp/language/statements)
- [Bitcoin Core Control Flow Examples](https://github.com/bitcoin/bitcoin)
- [C++ Best Practices](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)