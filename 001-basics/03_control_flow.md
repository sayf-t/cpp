# Control Flow in C++

This tutorial covers the various control flow statements in C++ that allow you to control the execution path of your program.

## 1. If Statements

### Basic If Statement
```cpp
if (condition) {
    // code to execute if condition is true
}
```

### If-Else Statement
```cpp
if (grade >= 60) {
    std::cout << "Passed!" << std::endl;
} else {
    std::cout << "Failed!" << std::endl;
}
```

### If-Else If-Else Chain
```cpp
if (grade >= 90) {
    std::cout << "A" << std::endl;
} else if (grade >= 80) {
    std::cout << "B" << std::endl;
} else if (grade >= 70) {
    std::cout << "C" << std::endl;
} else {
    std::cout << "F" << std::endl;
}
```

## 2. Switch Statements

```cpp
char grade = 'B';
switch (grade) {
    case 'A':
        std::cout << "Excellent!" << std::endl;
        break;
    case 'B':
        std::cout << "Good job!" << std::endl;
        break;
    case 'C':
        std::cout << "Fair" << std::endl;
        break;
    default:
        std::cout << "Invalid grade" << std::endl;
}
```

## 3. Loops

### While Loop
```cpp
int count = 0;
while (count < 5) {
    std::cout << count << " ";
    count++;
}
```

### Do-While Loop
```cpp
int num;
do {
    std::cout << "Enter a positive number: ";
    std::cin >> num;
} while (num <= 0);
```

### For Loop
```cpp
for (int i = 0; i < 5; i++) {
    std::cout << i << " ";
}
```

### Range-Based For Loop (C++11 and later)
```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};
for (const auto& num : numbers) {
    std::cout << num << " ";
}
```

## 4. Break and Continue

### Break Statement
```cpp
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        break;  // exits the loop
    }
    std::cout << i << " ";
}
```

### Continue Statement
```cpp
for (int i = 0; i < 5; i++) {
    if (i == 2) {
        continue;  // skips rest of the loop body
    }
    std::cout << i << " ";
}
```

## Practice Programs

### 1. Number Guessing Game
```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed random number generator
    srand(time(0));
    
    // Generate random number between 1 and 100
    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    
    do {
        std::cout << "Enter your guess (1-100): ";
        std::cin >> guess;
        attempts++;
        
        if (guess > secretNumber) {
            std::cout << "Too high!" << std::endl;
        } else if (guess < secretNumber) {
            std::cout << "Too low!" << std::endl;
        } else {
            std::cout << "Correct! You took " << attempts << " attempts." << std::endl;
        }
    } while (guess != secretNumber);
    
    return 0;
}
```

### 2. Simple Calculator
```cpp
#include <iostream>

int main() {
    char operation;
    double num1, num2;
    
    std::cout << "Enter first number: ";
    std::cin >> num1;
    std::cout << "Enter operation (+, -, *, /): ";
    std::cin >> operation;
    std::cout << "Enter second number: ";
    std::cin >> num2;
    
    switch (operation) {
        case '+':
            std::cout << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
            break;
        case '-':
            std::cout << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;
            break;
        case '*':
            std::cout << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
            break;
        case '/':
            if (num2 != 0) {
                std::cout << num1 << " / " << num2 << " = " << num1 / num2 << std::endl;
            } else {
                std::cout << "Error: Division by zero!" << std::endl;
            }
            break;
        default:
            std::cout << "Invalid operation!" << std::endl;
    }
    
    return 0;
}
```

## Practice Exercises

1. Write a program that prints all even numbers between 1 and 20
2. Create a program that finds the factorial of a number using a loop
3. Implement a simple menu-driven program using switch statements
4. Write a program that validates user input using a do-while loop

## Common Mistakes to Avoid

1. Forgetting break statements in switch cases
2. Infinite loops due to incorrect conditions
3. Off-by-one errors in loop conditions
4. Using = instead of == in conditions
5. Forgetting to initialize loop variables

## Key Concepts Learned

- Conditional statements (if, if-else, switch)
- Different types of loops (while, do-while, for)
- Break and continue statements
- Nested control structures
- Input validation techniques

## Next Steps

Now that you understand control flow, you're ready to move on to [Functions](04_functions.md)! 

<!--
EXERCISE 1: Transaction Fee Calculator
----------------------------------------
Using concepts: if-else chains, basic arithmetic

Write a program that:
1. Ask user for transaction amount in BTC
2. Calculate fee based on amount:
   - If amount < 0.001 BTC: fee = 1%
   - If 0.001 <= amount < 0.01 BTC: fee = 0.5%
   - If 0.01 <= amount < 0.1 BTC: fee = 0.2%
   - If amount >= 0.1 BTC: fee = 0.1%
3. Print both fee amount and final amount after fee

Example structure:
INPUT amount
IF amount < 0.001
    fee = amount * 0.01
ELSE IF amount < 0.01
    fee = amount * 0.005
...and so on
PRINT "Fee: " + fee
PRINT "Final amount: " + (amount + fee)
-->

<!-- EXERCISE 2: Block Confirmation Counter
----------------------------------------
Using concepts: while loop, switch, break

Write a program that:
1. Start with confirmations = 0
2. In a loop, ask user for block status:
   'n' = new block found
   'r' = chain reorg (remove last confirmation)
   'q' = quit checking
3. Keep track of confirmations (minimum 0)
4. Print "Transaction Confirmed!" when confirmations reach 6

Example structure:
confirmations = 0
WHILE true
    PRINT "Current confirmations: " + confirmations
    INPUT action
    
    SWITCH action
        CASE 'n':
            increment confirmations
            IF confirmations >= 6
                PRINT "Transaction Confirmed!"
                BREAK from loop
        CASE 'r':
            IF confirmations > 0
                decrement confirmations
        CASE 'q':
            BREAK from loop
        DEFAULT:
            PRINT "Invalid input"
    
    IF confirmations < 0
        confirmations = 0 -->

<!-- EXERCISE 3: Transaction Batch Processor
----------------------------------------
Using concepts: for loops, if-else, continue, input validation

Write a program that:
1. Ask user how many transactions to process
2. For each transaction:
   - Get amount and fee
   - Validate inputs (no negative values)
   - Skip transaction if invalid (use continue)
   - Track total amount and fees
3. Print summary at end

Example structure:
INPUT number_of_transactions
total_amount = 0
total_fees = 0

FOR i from 1 to number_of_transactions
    PRINT "Transaction " + i
    INPUT amount
    INPUT fee
    
    IF amount < 0 OR fee < 0
        PRINT "Invalid transaction, skipping"
        CONTINUE to next iteration
    
    IF fee > amount * 0.1
        PRINT "Warning: High fee!"
    
    total_amount = total_amount + amount
    total_fees = total_fees + fee

PRINT "Processed " + number_of_transactions + " transactions"
PRINT "Total amount: " + total_amount
PRINT "Total fees: " + total_fees -->