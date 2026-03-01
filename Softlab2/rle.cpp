#include <iostream>
#include <string>
#include <cctype>

// ------------------- RLE ENCODE -------------------
std::string rle_encode(const std::string& input) {
    if (input.empty()) return "";

    std::string output;
    int count = 1;

    for (size_t i = 1; i <= input.size(); ++i) {
        if (i < input.size() && input[i] == input[i - 1]) {
            count++;
        } else {
            output += std::to_string(count);
            output += input[i - 1];
            count = 1;
        }
    }

    return output;
}
// ------------------- RLE DECODE -------------------
std::string rle_decode(const std::string& input) {
    std::string output;
    int count = 0;
    bool readingCount = true;

    for (char c : input) {
        if (readingCount) {
            if (std::isdigit(c)) {
                count = count * 10 + (c - '0');
            }
        } else {
            output.append(count, c);
            count = 0;
            readingCount = true;
        }
    }

    return output;
}
// ------------------- INTERACTIVE SHELL -------------------
int main() {
    while (true) {
        std::cout << "\nRLE Interactive Shell\n";
        std::cout << "1. Encode\n";
        std::cout << "2. Decode\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // clear newline from buffer

        if (choice == 3) {
            std::cout << "Exiting...\n";
            break;
        }

        std::string input;
        std::cout << "Enter string: ";
        std::getline(std::cin, input);

        if (choice == 1) {
            std::string encoded = rle_encode(input);
            std::cout << "Encoded: " << encoded << "\n";
        }
        else if (choice == 2) {
            std::string decoded = rle_decode(input);
            std::cout << "Decoded: " << decoded << "\n";
        }
        else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
