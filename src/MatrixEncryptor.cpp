#include "MatrixEncryptor.h"
#include <random>
#include <iostream>
#include <sstream>

Eigen::MatrixXd MatrixEncryptor::generateRandomKey(int size) {
    Eigen::MatrixXd key(size, size);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(-10.0, 10.0);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            key(i, j) = distribution(generator);
        }
    }
    return key;
}

MatrixEncryptor::MatrixEncryptor(int size) {
    keyMatrix = generateRandomKey(size);
}

MatrixEncryptor::MatrixEncryptor(const Eigen::MatrixXd& customKey) : keyMatrix(customKey) {}

std::vector<int> MatrixEncryptor::encrypt(const std::vector<int>& message) const {
    int size = keyMatrix.rows();
    int messageSize = message.size();
    std::cout << messageSize << std::endl;
    std::cout << size << std::endl;
    int remainder = size - (messageSize % size);
    std::vector<int> paddedMessage = message;
    paddedMessage.insert(paddedMessage.end(), remainder, ' '); // Padding message with spaces to make its size a multiple of the key matrix size

    std::vector<int> encrypted_message;
    for (int i = 0; i < paddedMessage.size(); i += size) {
        Eigen::VectorXd messageVector(size);
        for (int j = 0; j < size; ++j) {
            messageVector(j) = paddedMessage[i + j];
        }
        Eigen::VectorXd encryptedVector = keyMatrix * messageVector;
        for (int j = 0; j < size; ++j) {
            encrypted_message.push_back(static_cast<int>(encryptedVector(j)));
        }
    }
    return encrypted_message;
}

std::vector<int> MatrixEncryptor::decrypt(const std::vector<int>& encrypted_message, int size) const {
    std::vector<int> decrypted_message;
    for (int i = 0; i < encrypted_message.size(); i += size) {
        Eigen::VectorXd encryptedVector(size);
        for (int j = 0; j < size; ++j) {
            encryptedVector(j) = encrypted_message[i + j];
        }
        Eigen::MatrixXd inverseKey = keyMatrix.inverse();
        Eigen::VectorXd decryptedVector = inverseKey * encryptedVector;
        for (int j = 0; j < size; ++j) {
            // Round to the nearest integer before converting back to int
            int decrypted_value = static_cast<int>(decryptedVector(j) + 0.5);
            decrypted_message.push_back(decrypted_value);
        }
    }
    return decrypted_message;
}

const Eigen::MatrixXd& MatrixEncryptor::getKey() const {
    return keyMatrix;
}

std::vector<int> MatrixEncryptor::parseInput(const std::string& input) {
    std::vector<int> parsed;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        for (char c : token) {
            parsed.push_back(static_cast<int>(c));
        }
        parsed.push_back(' '); // Add space after each token
    }
    return parsed;
}

Eigen::MatrixXd MatrixEncryptor::getCustomKey(int size) {
    Eigen::MatrixXd customKey(size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cin >> customKey(i, j);
        }
    }
    return customKey;
}

