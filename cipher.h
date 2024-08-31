#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Checks the validity of the command line arguments
void checkArguments(int argc, char* argv[]);

// Reads the content of a file and returns it as a vector of characters
std::vector<char> readFile(const std::string& filename);

// Writes data (vector of characters) to a file
void writeFile(const std::string& filename, const std::vector<char>& data);

// Processes the input data using the block cipher method
std::vector<char> processBlockCipher(const std::vector<char>& input, const std::vector<char>& key, char mode);

// Processes the input data using the stream cipher method
std::vector<char> processStreamCipher(const std::vector<char>& input, const std::vector<char>& key);

#endif // CIPHER_H
