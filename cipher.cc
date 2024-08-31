#include "cipher.h"
using namespace std;

int main(int argc, char* argv[]) {
    try {
        // Check if the command line arguments are valid
        checkArguments(argc, argv);

        // Retrieve the type of cipher function (Block or Stream) and mode of operation (Encrypt or Decrypt)
        char functionType = argv[1][0];  // 'B' for Block, 'S' for Stream
        char mode = argv[5][0];  // 'E' for Encrypt, 'D' for Decrypt

        // Read the input and key files
        vector<char> input = readFile(argv[2]);  // Input data
        vector<char> key = readFile(argv[4]);    // Encryption/Decryption key
        vector<char> output;

        // If the input file is empty, write an empty output file and exit
        if (input.empty()) {
            writeFile(argv[3], output);
            return 0;
        }

        // Process the input data using the specified cipher function
        if (functionType == 'B') {
            output = processBlockCipher(input, key, mode);
        } else if (functionType == 'S') {
            output = processStreamCipher(input, key);
        }

        // Write the processed data to the output file
        writeFile(argv[3], output);
    } catch (const exception& e) {
        // Catch and display any errors
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

void checkArguments(int argc, char* argv[]) {
    // Validate the number of command line arguments
    if (argc != 6) {
        throw runtime_error("Incorrect number of arguments");
    }
    // Validate the cipher function type
    if (argv[1][0] != 'B' && argv[1][0] != 'S') {
        throw runtime_error("First argument must be 'B' or 'S'");
    }
    // Validate the mode of operation
    if (argv[5][0] != 'E' && argv[5][0] != 'D') {
        throw runtime_error("Fifth argument must be 'E' or 'D'");
    }
}

vector<char> readFile(const string& filename) {
    // Open the file and read its contents into a vector of characters
    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("File " + filename + " not found");
    }
    return vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

void writeFile(const string& filename, const vector<char>& data) {
    // Open the file and write the data to it
    ofstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Unable to open file " + filename);
    }
    file.write(data.data(), data.size());
}

vector<char> processBlockCipher(const vector<char>& input, const vector<char>& key, char mode) {
	vector<char> output;
	if (mode == 'E') {
		// Encrypt the input data using the key
		size_t blockStart = 0;
		while (blockStart < input.size()) {
			vector<char> block(input.begin() + blockStart, input.begin() + min(blockStart + key.size(), input.size()));

			// Pad the block if needed
			if (block.size() < key.size()) {
				for (size_t i = block.size(); i < key.size(); i++) {
					block.push_back(0x81);
				}
			}

			// XOR the block with the key
			for (size_t j = 0; j < block.size(); j++) {
				block[j] ^= key[j];
			}

			// Swap algorithm
    		vector<char>::iterator start = block.begin();
			vector<char>::iterator end = block.end() - 1;
			while (start < end) {
				for (char byte : key) {
					bool swap = byte % 2;
					if (swap) {
						iter_swap(start, end);
						end--;
					}
					start++;
					if (start >= end) {
						break;
					}
				}
			}

			// Append the encrypted block to the output and move to next block
			output.insert(output.end(), block.begin(), block.end());
			blockStart += key.size();
		}

	}

	else if (mode == 'D') {
		// Decrypt the input data using the key
		size_t blockStart = 0;
		while (blockStart < input.size()) {
			vector<char> block(input.begin() + blockStart, input.begin() + min(blockStart + key.size(), input.size()));

			// Reverse the Swap algorithm
			vector<char>::iterator start = block.end() - 1;
			vector<char>::iterator end = block.begin();
			while (start > end) {
				for (char byte : key) {
					bool swap = byte % 2;
					if (swap) {
						iter_swap(start, end);
						start--;
					}
					end++;
					if (start <= end) {
						break;
					}
				}
			}

			// XOR the block with the key
			for (size_t j = 0; j < block.size(); j++) {
				block[j] ^= key[j];
			}

			// Remove padding if necessary
			while (!block.empty() && block.back() == 0x81) {
				block.pop_back();
			}

			// Append the decrypted block to the output and move to next block
			output.insert(output.end(), block.begin(), block.end());
			blockStart += key.size();
		}

	}

    return output;
}

vector<char> processStreamCipher(const vector<char>& input, const vector<char>& key) {
    vector<char> output;
    size_t i = 0; // Key index
    for (auto c : input) {
        // XOR each byte of the input with the corresponding byte of the key
        output.push_back(c ^ key[i]);

        // Increment key index and wrap around if it reaches the end of the key
        i = (i + 1) % key.size();
    }

    return output;
}
