#ifndef CIPHER_H
#define CIPHER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
void saveData(const std::string &filename, const std::vector<char> &data);
std::vector<char> executeStreamCipher(const std::vector<char> &input, const std::vector<char> &key);
void validateInputs(int argc, char *argv[]);
std::vector<char> executeBlockCipher(const std::vector<char> &input, const std::vector<char> &key, char mode);
std::vector<char> readData(const std::string &filename);
#endif
