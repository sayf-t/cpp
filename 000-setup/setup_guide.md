# Setting Up Your C++ Development Environment

This guide will help you set up everything you need to start programming in C++.

## 1. Installing a C++ Compiler

### For macOS:
1. Open Terminal
2. Install Xcode Command Line Tools:
   ```bash
   xcode-select --install
   ```
3. Verify installation:
   ```bash
   g++ --version
   ```

### For Windows:
1. Download MinGW-w64 from [MinGW-w64 Website](https://www.mingw-w64.org/)
2. Run the installer and follow the installation steps
3. Add MinGW's bin directory to your system's PATH
4. Verify installation:
   ```bash
   g++ --version
   ```

### For Linux:
1. Open Terminal
2. Install GCC:
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential
   ```
3. Verify installation:
   ```bash
   g++ --version
   ```

## 2. Installing an IDE/Text Editor

Choose one of these options:

### Visual Studio Code (Recommended)
1. Download from [VS Code Website](https://code.visualstudio.com/)
2. Install these extensions:
   - C/C++ by Microsoft
   - C/C++ Extension Pack
   - Code Runner (optional)

### CLion
- Professional IDE by JetBrains
- Download from [CLion Website](https://www.jetbrains.com/clion/)
- Free for students with educational email

### Visual Studio
- Download from [Visual Studio Website](https://visualstudio.microsoft.com/)
- Select "Desktop development with C++" during installation

## 3. Creating Your First Project

1. Create a new directory for your C++ projects:
   ```bash
   mkdir cpp_projects
   cd cpp_projects
   ```

2. Create a test file:
   ```bash
   touch hello.cpp
   ```

3. Open in your chosen editor and add this code:
   ```cpp
   #include <iostream>
   
   int main() {
       std::cout << "Hello, C++!" << std::endl;
       return 0;
   }
   ```

4. Compile and run:
   ```bash
   g++ hello.cpp -o hello
   ./hello
   ```

## 4. Setting Up Version Control (Optional but Recommended)

1. Install Git from [Git Website](https://git-scm.com/)
2. Configure Git:
   ```bash
   git config --global user.name "Your Name"
   git config --global user.email "your.email@example.com"
   ```

## Troubleshooting Common Issues

### Common Error: 'g++' not found
- Make sure the compiler is properly installed
- Check if PATH is correctly set
- Try restarting your terminal/computer

### IDE Not Detecting Compiler
- Make sure compiler path is correctly set in IDE settings
- Restart IDE after installing compiler
- Check if all required extensions are installed

## Next Steps

Once you have your environment set up, you're ready to move on to [Your First C++ Program](../basics/01_hello_world.md)!

Remember:
- Test your setup with a simple program
- Make sure you can compile and run code
- Get familiar with your chosen IDE
- Don't hesitate to use online resources if you encounter issues 