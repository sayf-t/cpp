# Your First C++ Program: Hello World

Welcome to your first C++ program! In this tutorial, we'll create a simple program that prints text to the screen. This will help you verify your setup and learn the basic structure of a C++ program.

## Learning Objectives
- Create and run your first C++ program
- Understand basic program structure
- Learn about comments and basic output
- Practice modifying and running code

## Verify Your Setup

Before we start coding, let's make sure everything is working:

1. Open your terminal and type:
   ```bash
   g++ --version
   ```
   You should see version information, not an error.

2. Create a project directory:
   ```bash
   mkdir cpp_learning
   cd cpp_learning
   ```

## Your First Program

### Step 1: Create the File
Create a new file called `hello.cpp` in your text editor.

### Step 2: Write the Code
Type the following code exactly as shown (don't copy-paste - typing helps learning!):

```cpp
// This is a comment - it helps explain the code
#include <iostream>

int main() {
    // Print a message to the screen
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Step 3: Understanding Each Part

Let's break down each line:

```cpp
// This is a comment - it helps explain the code
```
- Comments start with `//`
- They're notes for humans, ignored by the computer
- Use them to explain your code

```cpp
#include <iostream>
```
- Tells the program to include input/output functionality
- Think of it as importing tools we need
- `iostream` lets us print text to the screen

```cpp
int main() {
```
- Every C++ program starts running from `main`
- `int` means the function returns a number
- The curly braces `{ }` contain the program code

```cpp
    std::cout << "Hello, World!" << std::endl;
```
- `std::cout` is used for output (printing)
- `<<` sends data to the output
- Text in quotes `"Hello, World!"` is printed exactly
- `std::endl` adds a new line

```cpp
    return 0;
```
- Tells the program we finished successfully
- `0` means "everything worked fine"

### Step 4: Compile and Run

1. Save your file
2. In the terminal, compile the program:
   ```bash
   g++ hello.cpp -o hello
   ```
3. Run your program:
   ```bash
   ./hello
   ```

You should see:
```
Hello, World!
```

## Common Problems and Solutions

### Problem 1: "Command not found"
```bash
g++: command not found
```
➡️ Solution: Your C++ compiler isn't installed. Return to the setup guide.

### Problem 2: Missing Semicolon
```cpp
std::cout << "Hello, World!" << std::endl    // Missing ;
```
➡️ Solution: Add a semicolon at the end of the line.

### Problem 3: Missing Quotes
```cpp
std::cout << Hello, World! << std::endl;    // Missing quotes
```
➡️ Solution: Put text in quotes: `"Hello, World!"`

## Practice Exercises

### 1. Basic Output
Modify the program to print your name:
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, [Your Name]!" << std::endl;
    return 0;
}
```

### 2. Multiple Lines
Print multiple lines of text:
```cpp
#include <iostream>

int main() {
    std::cout << "Line 1" << std::endl;
    std::cout << "Line 2" << std::endl;
    std::cout << "Line 3" << std::endl;
    return 0;
}
```

### 3. ASCII Art
Create a simple pattern:
```cpp
#include <iostream>

int main() {
    std::cout << "*****" << std::endl;
    std::cout << "****" << std::endl;
    std::cout << "***" << std::endl;
    std::cout << "**" << std::endl;
    std::cout << "*" << std::endl;
    return 0;
}
```

## Knowledge Check

Try to answer these questions:
1. What does `#include <iostream>` do?
2. Why do we need `main()`?
3. What does `std::cout` do?
4. Why do we use `<<` symbols?
5. What happens if you forget a semicolon?

## Bitcoin Connection

While this program is simple, it introduces concepts we'll use when working with Bitcoin:
- Comments for documenting code (crucial for complex cryptocurrency systems)
- Proper code structure (vital for secure financial software)
- Error checking (essential for handling money safely)
- Output formatting (important for displaying transaction information)

## Next Steps

1. **Experiment!** Try:
   - Printing different messages
   - Adding more lines of output
   - Creating your own ASCII art

2. **Common Challenges:**
   - Remove semicolons and see what errors you get
   - Try different text and symbols
   - Add more comments to explain your code

3. When you're comfortable with this program, move on to [Variables and Data Types](02_variables_and_types.md)

Remember:
- Type the code yourself instead of copying
- Make sure each program compiles before moving on
- Experiment with the code to learn more
- Don't worry about making mistakes - they help you learn!