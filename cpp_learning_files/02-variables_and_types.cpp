#include <iostream>
#include <iomanip>




// #include <array>
// #include <algorithm>

// int main() {
//     std::array<double, 5> transactions = {0};
//     double runningBalance = 0.0;

// // Record transactions
//     transactions[0] = 0.5;   // First deposit
//     transactions[1] = -0.2;  // Withdrawal
//     transactions[2] = 0.3;   // Another deposit
//     transactions[3] = -0.1;  // Another withdrawal
//     transactions[4] = 0.4;   // Final deposit

//     // Update running balance
//     for (double tx : transactions) {
//         runningBalance += tx;
//     }
    
//     // Find highest and lowest
//     double highest = *std::max_element(transactions.begin(), transactions.end());
//     double lowest = *std::min_element(transactions.begin(), transactions.end());

//         std::cout << std::fixed << std::setprecision(8);
//     std::cout << "Final Balance: " << runningBalance << " BTC\n";
//     std::cout << "Largest Transaction: " << highest << " BTC\n";
//     std::cout << "Smallest Transaction: " << lowest << " BTC\n";
    
//     return 0;
// }

// Multi Currency Display
// int main() {
//     double btcAmount = 0.5;
//     double usdRate = 45000.0;
//     double usdAmount = btcAmount * usdRate;

//     std::cout << std::fixed << std::setprecision(8);
//     std::cout << "BTC: " << btcAmount << std::endl;
    
//     std::cout << std::fixed << std::setprecision(2);
//     std::cout << "USD: $" << usdAmount << std::endl;
    
//     return 0;
// }

// Simple transaction calculator

// int main() {
//     double btcAmount = 0.01;
//     int satoshisPerBTC = 100000000;
//     int satoshiAmount;
//     bool hasSufficientFunds = true;

//     satoshiAmount = btcAmount * satoshisPerBTC;

//     std::cout.imbue(std::locale("en_US.UTF-8"));
//     std::cout << "Transaction Amount (BTC): " << btcAmount << std::endl;
//     std::cout << "Amount in satoshis: " << satoshiAmount << std::endl;
//     std::cout << "Can proceed: " << std::boolalpha << hasSufficientFunds << std::endl;

//     return 0;
// }

// Temperature converter

// int main() {
//     double celsius = 40.0;
//     double fahrenheit;

//     fahrenheit = (celsius * 9.0/5.0) + 32.0;

//     std::cout << celsius << "°C = " << fahrenheit << "°F" << std::endl;

//     return 0;
// }


// # Wallet exercise

// int main () {
//     double bitcoinBalance = 0.05;
//     int satoshiBalance = 5000000;
//     bool isNewWallet = true;
//     char walletType = 'P';

//     std::cout << "=== My first Wallet ===" << std::endl;
//     std::cout << "Balance (BTC): " << bitcoinBalance << std::endl;
//     std::cout << "Balance (satoshis): " << satoshiBalance << std::endl;
//     std::cout << "New Wallet: " << std::boolalpha << isNewWallet << std::endl;
//     std::cout << "Wallet Type: " << walletType << std::endl;

//     return 0;
// }

// Experimentation section
// int main() {
//     // Different mathematical operations
//     double a = 10.5, b = 2.5;
//     double sum = a + b;
//     double difference = a - b;
//     double product = a * b;
//     double quotient = a / b;

//     std::cout << "Sum: " << sum << ", Difference: " << difference 
//               << ", Product: " << product << ", Quotient: " << quotient << std::endl;

//     // Converting between types
//     double btcAmount = 0.01;
//     int satoshisPerBTC = 100000000;
//     int satoshiAmount;
//     satoshiAmount = btcAmount * satoshisPerBTC;
//     std::cout << "Converted BTC to int: " << satoshiAmount << std::endl;

//     // Printing different formats... see https://en.cppreference.com/w/cpp/io/manip
//     std::cout << std::fixed << std::setprecision(2);
//     std::cout << "Formatted BTC Amount: " << btcAmount << std::endl;

//     // Challenge Yourself: More complex wallet program
//     double transactionAmount = 0.01; // BTC
//     double transactionFeePercentage = 0.01; // 1%
//     double bitcoinBalance = 0.05; // BTC
//     double transactionFee = transactionAmount * transactionFeePercentage;
//     double newBalance = bitcoinBalance - transactionAmount - transactionFee;

    // std::cout << "Transaction Amount (BTC): " << transactionAmount << std::endl;
    // std::cout << std::fixed << std::setprecision(8);
    // std::cout << "Transaction Fee (BTC): " << transactionFee << std::endl;
    // // std::cout << std::setprecision(2);
    // std::cout << "New Balance (BTC): " << newBalance << std::endl;

    // // Transaction history variables
    // std::string transactionHistory = "Transaction: " + std::to_string(transactionAmount) + " BTC, Fee: " + std::to_string(transactionFee) + " BTC";
    // std::cout << "Transaction History: " << transactionHistory << std::endl;

    // Print a formatted table
//     std::cout << "\n=== Transaction Summary ===" << std::endl;
//     std::cout << std::fixed << std::setprecision(2); // Set precision for the first two columns
//     std::cout << std::setw(20) << "Description" 
//               << std::setw(20) << "Amount (BTC)" 
//               << std::setw(20) << "Transaction Fee (BTC)" 
//               << std::setw(20) << "New Balance (BTC)" << std::endl;

//     std::cout << std::setprecision(8); // Set precision for the transaction fee
//     std::cout << std::setw(20) << "Transaction" 
//               << std::setw(20) << transactionAmount 
//               << std::setw(20) << transactionFee 
              
//               << std::setw(20) << newBalance << std::endl;

//     return 0;
// }

