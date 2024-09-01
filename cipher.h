#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
void argumentValidation(int argc, char *argv[]);
std::vector<char> readFile(const std::string &filename);
void writeFile(const std::string &filename, const std::vector<char> &data);
std::vector<char> processBlockCipher(const std::vector<char> &input, const std::vector<char> &key, char mode);
std::vector<char> processStreamCipher(const std::vector<char> &input, const std::vector<char> &key);
#endif
