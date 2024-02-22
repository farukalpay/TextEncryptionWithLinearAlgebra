#ifndef MATRIXENCRYPTOR_H
#define MATRIXENCRYPTOR_H

#include <Eigen/Dense>
#include <vector>
#include <string>

class MatrixEncryptor {
private:
    Eigen::MatrixXd keyMatrix;

    Eigen::MatrixXd generateRandomKey(int size);

public:
    MatrixEncryptor(int size);
    MatrixEncryptor(const Eigen::MatrixXd& customKey);

    std::vector<int> encrypt(const std::vector<int>& message) const;
    std::vector<int> decrypt(const std::vector<int>& encrypted_message, int size) const;
    const Eigen::MatrixXd& getKey() const;

    static std::vector<int> parseInput(const std::string& input);
    static Eigen::MatrixXd getCustomKey(int size);
    static size_t calculateHash(const std::vector<int>& data);
};

#endif // MATRIXENCRYPTOR_H
