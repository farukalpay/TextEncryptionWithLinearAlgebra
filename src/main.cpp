#include <iostream>
#include "InputHandler.h"

int main() {
    int choice;
    do {
        std::cout << "(1) Encrypt a text" << std::endl;
        std::cout << "(2) Decrypt a text" << std::endl;
        std::cout << "(3) Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            InputHandler::encryptText();
            break;
        case 2:
            InputHandler::decryptText();
            break;
        case 3:
            std::cout << "Exiting program..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);

    return 0;
}
