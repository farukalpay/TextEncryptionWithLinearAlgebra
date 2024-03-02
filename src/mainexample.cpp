#include "MatrixEncryptor.h"
#include <iostream>

int main() {
    // Example using randomly generated key
    MatrixEncryptor encryptor(3); // Create an encryptor with a 3x3 randomly generated key

    // Original message
    std::string message = "Hi";
    // Encrypt the original message
    std::vector<int> encrypted_message = encryptor.encrypt(MatrixEncryptor::parseInput(message));

    // Print encrypted message
    std::cout << "Encrypted message:" << std::endl;
    for (int encrypted_char : encrypted_message) {
        std::cout << encrypted_char << " ";
    }
    std::cout << std::endl;

    // Decrypt the encrypted message
    std::vector<int> decrypted_message = encryptor.decrypt(encrypted_message, 3);
    // Print decrypted message
    std::cout << "Decrypted message: ";
    for (int decrypted_char : decrypted_message) {
        std::cout << static_cast<char>(decrypted_char);
    }
    std::cout << std::endl;

    // Example using custom key
    std::cout << "Enter a 3x3 custom key:" << std::endl;
    // Get custom key from user input
    Eigen::MatrixXd customKey = MatrixEncryptor::getCustomKey(3);
    // Create an encryptor with the custom key
    MatrixEncryptor encryptor_custom(customKey);

    // Another message to encrypt
    std::string message_custom = "hi";
    // Encrypt the custom message
    std::vector<int> encrypted_message_custom = encryptor_custom.encrypt(MatrixEncryptor::parseInput(message_custom));

    // Print encrypted message with custom key
    std::cout << "Encrypted message with custom key:" << std::endl;
    for (int encrypted_char : encrypted_message_custom) {
        std::cout << encrypted_char << " ";
    }
    std::cout << std::endl;

    // Decrypt the encrypted message with custom key
    std::vector<int> decrypted_message_custom = encryptor_custom.decrypt(encrypted_message_custom, 3);
    // Print decrypted message with custom key
    std::cout << "Decrypted message with custom key: ";
    for (int decrypted_char : decrypted_message_custom) {
        std::cout << static_cast<char>(decrypted_char);
    }
    std::cout << std::endl;

    return 0;
}
