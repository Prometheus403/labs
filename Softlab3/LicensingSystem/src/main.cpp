#include "LicenseManager.h"
#include <iostream>

int main() {
    std::cout << "1 - Create Perpetual License\n";
    std::cout << "2 - Create 30-day License\n";
    std::cout << "3 - Validate License\n";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            LicenseManager::CreateLicense(false);
            std::cout << "Perpetual license created\n";
            break;
        case 2:
            LicenseManager::CreateLicense(true);
            std::cout << "30-day license created\n";
            break;
        case 3:
            std::cout << (LicenseManager::ValidateLicense()
                          ? "License VALID\n"
                          : "License INVALID\n");
            break;
        default:
            std::cerr << "Invalid choice\n";
            return 1;
    }

    return 0;
}
