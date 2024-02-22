#include "InputHandler.h"
#include "MatrixEncryptor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstdlib> // For system() function
#include <Eigen/Dense>

void clearScreen() {
#ifdef _WIN32
    std::system("cls"); // Clear screen for Windows
#else
    std::system("clear"); // Clear screen for Unix-like systems
#endif
}

void displayEncryptionOptions() {
    std::cout << "Options:" << std::endl;
    std::cout << "(1) Show Encrypted Data" << std::endl;
    std::cout << "(2) Save Encrypted Data" << std::endl;
    std::cout << "(3) Show Key" << std::endl;
    std::cout << "(4) Save Key" << std::endl;
    std::cout << "(5) Show All Values" << std::endl;
    std::cout << "(6) Back to Menu" << std::endl;
    std::cout << "(7) Exit" << std::endl;
}

void displayDecryptionOptions() {
    std::cout << "Options:" << std::endl;
    std::cout << "(1) Show Decrypted Data" << std::endl;
    std::cout << "(2) Save Decrypted Data" << std::endl;
    std::cout << "(3) Back to Menu" << std::endl;
    std::cout << "(4) Exit" << std::endl;
}

void InputHandler::encryptText() {

    char textChoice;
    std::vector<int> message;
    clearScreen();
    std::cout << "Do you want to enter the text manually or load it from a file? (m/f): ";
    std::cin >> textChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (textChoice == 'm' || textChoice == 'M') {
        std::cout << "Enter the text to encrypt: ";
        std::string input_text;
        std::getline(std::cin, input_text);
        message = MatrixEncryptor::parseInput(input_text);
    }
    else if (textChoice == 'f' || textChoice == 'F') {
        std::string filename;
        std::cout << "Enter the path to the file containing the data: ";
        std::getline(std::cin, filename);
        std::vector<char> fileText = readTextFromFile(filename);

        // Check if the file contains valid data
        if (fileText.empty()) {
            std::cout << "The file does not contain any valid data to encrypt." << std::endl;
            return;
        }

        // Convert file text to vector of ints if needed
        message.clear(); // Clear any existing data
        for (char ch : fileText) {
            // Convert char to int (ASCII value)
            message.push_back(static_cast<int>(ch));
        }
    }
    else {
        clearScreen();
        std::cout << "Invalid choice. Aborting encryption." << std::endl;
        return;
    }

    int keySize = message.size();

    char keyChoice;
    std::cout << "Do you want to use a custom key or generate it automatically? (c/g): ";
    std::cin >> keyChoice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    MatrixEncryptor encryptor(keySize);

    if (keyChoice == 'c' || keyChoice == 'C') {
        std::cout << "Enter the elements of the key matrix:" << std::endl;
        Eigen::MatrixXd customKey = MatrixEncryptor::getCustomKey(keySize);
        encryptor = MatrixEncryptor(customKey);
    }
    else if (keyChoice != 'g' && keyChoice != 'G') {
        clearScreen();
        std::cout << "Invalid choice. Aborting encryption." << std::endl;
        return;
    }

    std::vector<int> encrypted_message = encryptor.encrypt(message);
    
    // Clear screen and inform the user about encryption completion
    clearScreen();

    // Options after encryption
    std::cout << "Encryption is completed." << std::endl;
    displayEncryptionOptions();

    while (true) {
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
        case 1:
            clearScreen();
            std::cout << "Encrypted data:\n";
            for (int num : encrypted_message) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
            break;
        case 2:
        {
            clearScreen();
            std::string fileloc;
            std::cout << "Enter the path and filename to save the encrypted data: ";
            std::cin.ignore();
            std::getline(std::cin, fileloc);
            saveToFile(encrypted_message, fileloc);
            std::cout << "Encrypted data saved." << std::endl;
            break;
        }
        case 3:
            clearScreen();
            std::cout << "Key used for encryption:" << std::endl;
            std::cout << encryptor.getKey() << std::endl;
            break;
        case 4:
        {
            clearScreen();
            std::string fileloc;
            std::cout << "Enter the path and filename to save the key matrix: ";
            std::cin.ignore();
            std::getline(std::cin, fileloc);
            saveKeyToFile(encryptor.getKey(), fileloc);
            std::cout << "Key matrix data saved." << std::endl;
            break;
        }
        case 5:
            clearScreen();
            std::cout << "Original text: \n";
            for (int num : message) {
                std::cout << static_cast<char>(num);
            }
            std::cout << "\n\nEncrypted data: \n";
            for (int num : encrypted_message) {
                std::cout << num << " ";
            }
            std::cout << "\n\nKey used for encryption:" << std::endl;
            std::cout << encryptor.getKey() << std::endl;
            break;
        case 6:
            clearScreen();
            return; // Back to Menu
        case 7:
            exit(0);
        default:
            clearScreen();
            std::cout << "Invalid choice. Exiting.." << std::endl;
            exit(0);
        }
        std::cout << "\n(1) Back\n(2) Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int backChoice;
        std::cin >> backChoice;
        if (backChoice == 1) {
            clearScreen();
            displayEncryptionOptions();
        }
        else if (backChoice == 2) {
            exit(0);
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void InputHandler::decryptText() {
    clearScreen();
    std::cout << "Do you want to enter the encrypted data manually or load it from a file? (m/f): ";
    char inputChoice;
    std::cin >> inputChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<int> input_encrypted_message;
    if (inputChoice == 'm' || inputChoice == 'M') {
        std::cout << "Enter the encrypted text to decrypt: ";
        std::string input_line;
        std::getline(std::cin, input_line);
        std::istringstream iss(input_line);
        int num;
        while (iss >> num) {
            input_encrypted_message.push_back(num);
        }
    }
    else if (inputChoice == 'f' || inputChoice == 'F') {
        std::string filename;
        std::cout << "Enter the path to the file containing the encrypted data: ";
        std::getline(std::cin, filename);
        input_encrypted_message = readEncryptedDataFromFile(filename);
    }
    else {
        clearScreen();
        std::cout << "Invalid choice. Aborting decryption." << std::endl;
        return;
    }

    if (!input_encrypted_message.empty()) {
        int keySize = input_encrypted_message.size() / 2;
        clearScreen();
        char keyChoice;
        std::cout << "Do you want to enter the key manually or load it from a file? (m/f): ";
        std::cin >> keyChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Eigen::MatrixXd decryptionKey;

        if (keyChoice == 'm' || keyChoice == 'M') {
            std::cout << "Enter the elements of the key matrix:" << std::endl;
            decryptionKey = MatrixEncryptor::getCustomKey(keySize);
        }
        else if (keyChoice == 'f' || keyChoice == 'F') {
            std::string keyFilename;
            std::cout << "Enter the path to the key file: ";
            std::getline(std::cin, keyFilename);
            decryptionKey = readKeyFromFile(keyFilename);
            if (decryptionKey.rows() != keySize || decryptionKey.cols() != keySize) {
                clearScreen();
                std::cout << "Invalid key size. Aborting decryption." << std::endl;
                return;
            }
        }
        else {
            clearScreen();
            std::cout << "Invalid choice. Aborting decryption." << std::endl;
            return;
        }
        clearScreen();
        MatrixEncryptor decryptor(decryptionKey);
        std::vector<int> decrypted_message = decryptor.decrypt(input_encrypted_message, keySize);
        std::cout << "Decryption is completed.\n";
        displayDecryptionOptions();

        while (true) {
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;
            switch (choice) {
            case 1:
                clearScreen();
                std::cout << "Decrypted text: ";
                for (int num : decrypted_message) {
                    std::cout << static_cast<char>(num);
                }
                std::cout << std::endl;
                break;
            case 2:
            {
                clearScreen();
                std::string fileloc;
                std::cout << "Enter the path and filename to save the decrypted data: ";
                std::cin.ignore();
                std::getline(std::cin, fileloc);
                saveToFile(decrypted_message, fileloc);
                std::cout << "Decrypted data saved." << std::endl;
                break;
            }
            case 3:
                clearScreen();
                return; // Back to Menu
            case 4:
                exit(0);
            default:
                clearScreen();
                std::cout << "Invalid choice. Exiting.." << std::endl;
                exit(0);
            }
            std::cout << "\n(1) Back\n(2) Exit" << std::endl;
            std::cout << "Enter your choice: ";
            int backChoice;
            std::cin >> backChoice;
            if (backChoice == 1) {
                clearScreen();
                displayDecryptionOptions();
            }
            else if (backChoice == 2) {
                exit(0);
            }
            else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }

        // Saving decrypted message
        saveToFile(decrypted_message, "decrypted_text.txt");
        std::cout << "Decrypted data saved to 'decrypted_text.txt'" << std::endl;
    }
    else {
        std::cout << "Empty message. Decryption aborted." << std::endl;
    }
}

void InputHandler::saveToFile(const std::vector<int>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int num : data) {
            file << static_cast<char>(num); // Convert ASCII value to character
        }
        file.close();
        std::cout << "Text saved to '" << filename << "'" << std::endl;
    }
    else {
        std::cerr << "Unable to open file for saving: " << filename << std::endl;
    }
}

void InputHandler::saveKeyToFile(const Eigen::MatrixXd& key, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << key;
        file.close();
        std::cout << "Key matrix saved to '" << filename << "'" << std::endl;
    }
    else {
        std::cerr << "Unable to open file for saving: " << filename << std::endl;
    }
}


Eigen::MatrixXd InputHandler::readKeyFromFile(const std::string& filename) {
    std::ifstream file(filename);
    Eigen::MatrixXd key;
    if (file.is_open()) {
        std::vector<std::vector<double>> matrixData;
        std::string line;
        while (std::getline(file, line)) {
            std::vector<double> row;
            std::istringstream iss(line);
            double num;
            while (iss >> num) {
                row.push_back(num);
            }
            matrixData.push_back(row);
        }

        int rows = matrixData.size();
        int cols = (rows > 0) ? matrixData[0].size() : 0;
        key.resize(rows, cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                key(i, j) = matrixData[i][j];
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
    return key;
}

std::vector<int> InputHandler::readEncryptedDataFromFile(const std::string& filename) {
    std::vector<int> data;
    std::ifstream file(filename);
    if (file.is_open()) {
        int num;
        while (file >> num) {
            data.push_back(num);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
    return data;
}

std::vector<char> InputHandler::readTextFromFile(const std::string& filename) {
    std::vector<char> data;
    std::ifstream file(filename);
    if (file.is_open()) {
        char ch;
        while (file.get(ch)) {
            data.push_back(ch);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
    return data;
}
