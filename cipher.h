#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void checkArgumentCorrectness(int argc, char *argv[]);
std::vector<char> reading_file(const std::string &filename);
void output_to_the_file(const std::string &filename, const std::vector<char> &data);
std::vector<char> bloc_cipher_input_validator(const std::vector<char> &input, const std::vector<char> &key, char mode);
std::vector<char> stream_cipher_input_validator(const std::vector<char> &input, const std::vector<char> &key);
#endif
