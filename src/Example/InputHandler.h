#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>
#include <string>
#include <Eigen/Dense>

class InputHandler {
public:
    static void saveToFile(const std::vector<int>& data, const std::string& filename);

    static void encryptText();
    static void decryptText();
    static void saveKeyToFile(const Eigen::MatrixXd& key, const std::string& filename);
    static Eigen::MatrixXd readKeyFromFile(const std::string& filename);
    static std::vector<int> readEncryptedDataFromFile(const std::string& filename);
    static std::vector<char> readTextFromFile(const std::string& filename);
};

#endif
