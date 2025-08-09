/*
    Big Integer Multiplication in C++
    ---------------------------------
    Author : TARACHAND JAKHAR
    GitHub : TARACHANDJAKHAR
    Email  : u23ai099@coed.svnit.ac.in
    Date   : 9/8/25
    License: MIT License


    Description:
    This program multiplies two arbitrarily large integers given as strings.
    It works by simulating manual multiplication (like how we do on paper):
    - Reverse both numbers to start from the least significant digit.
    - Multiply each digit of first number with each digit of second number.
    - Append zeroes for place values.
    - Add partial products to get the final result.
    - Handles numbers much larger than standard int/long long limits.

    Special Handling:
    - Removes leading zeros in the result.
    - If either input is "0", returns "0".
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to multiply two string numbers and return result as string
string multiplyStrings(string num1, string num2) {
    // If any number is zero, product is zero
    if (num1 == "0" || num2 == "0") return "0";

    // Reverse both strings for easier digit-by-digit multiplication
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    string ans = "0"; // Final result starts as "0"
    int count = 0;    // Tracks position (for appending zeros in partial product)

    // Multiply each digit of num1 with each digit of num2
    for (char a : num1) {
        string temp(count, '0'); // Append zeros according to place value
        int carry = 0;

        for (char b : num2) {
            int p = a - '0'; // Convert char to int
            int q = b - '0'; // Convert char to int
            int result = p * q + carry; // Multiply and add carry
            temp.push_back((result % 10) + '0'); // Store last digit
            carry = result / 10; // Update carry
        }
        if (carry > 0) temp.push_back(carry + '0'); // Add last carry if exists
        reverse(temp.begin(), temp.end()); // Reverse to normal order

        // Make lengths equal before addition
        if (ans.length() < temp.length())
            ans.insert(ans.begin(), temp.length() - ans.length(), '0');
        if (temp.length() < ans.length())
            temp.insert(temp.begin(), ans.length() - temp.length(), '0');

        // Add temp to ans (string-based addition)
        string sum;
        int carry2 = 0;
        for (int i = ans.length() - 1; i >= 0; --i) {
            int digitSum = (ans[i] - '0') + (temp[i] - '0') + carry2;
            sum.push_back((digitSum % 10) + '0');
            carry2 = digitSum / 10;
        }
        if (carry2) sum.push_back(carry2 + '0'); // Add final carry
        reverse(sum.begin(), sum.end()); // Reverse to correct order
        ans = sum; // Update final result

        count++; // Move to next digit's place value
    }

    // Remove leading zeros from result
    int pos = ans.find_first_not_of('0');
    if (pos != string::npos) ans = ans.substr(pos);
    else ans = "0";

    return ans;
}

int main() {
    string str1, str2;

    // Input numbers as strings
    cout << "Enter first number: ";
    getline(cin, str1);
    cout << "Enter second number: ";
    getline(cin, str2);

    // Output the product
    cout << "Product: " << multiplyStrings(str1, str2) << "\n";

    return 0;
}
