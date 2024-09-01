#include "cipher.h"
using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		argumentValidation(argc, argv);
		char functionType = argv[1][0];
		char mode = argv[5][0];

		vector<char> input = readFile(argv[2]);
		vector<char> key = readFile(argv[4]);
		vector<char> output;

		if (input.empty())
		{
			writeFile(argv[3], output);
			return 0;
		}

		if (functionType == 'B')
		{
			output = processBlockCipher(input, key, mode);
		}
		else if (functionType == 'S')
		{
			output = processStreamCipher(input, key);
		}

		writeFile(argv[3], output);
	}
	catch (const exception &e)
	{
		cerr << "Error: " << e.what() << endl;
		return 1;
	}

	return 0;
}

void argumentValidation(int argc, char *argv[])
{
	if (argc != 6)
	{
		throw runtime_error("Incorrect number of arguments");
	}
	if (argv[1][0] != 'B' && argv[1][0] != 'S')
	{
		throw runtime_error("First argument must be 'B' or 'S'");
	}
	if (argv[5][0] != 'E' && argv[5][0] != 'D')
	{
		throw runtime_error("Fifth argument must be 'E' or 'D'");
	}
}

vector<char> readFile(const string &filename)
{
	ifstream file(filename, ios::binary);
	if (!file)
	{
		throw runtime_error("File " + filename + " not found");
	}
	return vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

void writeFile(const string &filename, const vector<char> &data)
{
	ofstream file(filename, ios::binary);
	if (!file)
	{
		throw runtime_error("Unable to open file " + filename);
	}
	file.write(data.data(), data.size());
}

vector<char> processBlockCipher(const vector<char> &input, const vector<char> &key, char mode)
{
	vector<char> output;
	if (mode == 'E')
	{
		size_t blockStart = 0;
		while (blockStart < input.size())
		{
			vector<char> block(input.begin() + blockStart, input.begin() + min(blockStart + key.size(), input.size()));

			if (block.size() < key.size())
			{
				for (size_t i = block.size(); i < key.size(); i++)
				{
					block.push_back(0x81);
				}
			}

			for (size_t j = 0; j < block.size(); j++)
			{
				block[j] ^= key[j];
			}

			vector<char>::iterator start = block.begin();
			vector<char>::iterator end = block.end() - 1;
			while (start < end)
			{
				for (char byte : key)
				{
					bool swap = byte % 2;
					if (swap)
					{
						iter_swap(start, end);
						end--;
					}
					start++;
					if (start >= end)
					{
						break;
					}
				}
			}

			output.insert(output.end(), block.begin(), block.end());
			blockStart += key.size();
		}
	}
	else if (mode == 'D')
	{
		size_t blockStart = 0;
		while (blockStart < input.size())
		{
			vector<char> block(input.begin() + blockStart, input.begin() + min(blockStart + key.size(), input.size()));

			vector<char>::iterator start = block.end() - 1;
			vector<char>::iterator end = block.begin();
			while (start > end)
			{
				for (char byte : key)
				{
					bool swap = byte % 2;
					if (swap)
					{
						iter_swap(start, end);
						start--;
					}
					end++;
					if (start <= end)
					{
						break;
					}
				}
			}

			for (size_t j = 0; j < block.size(); j++)
			{
				block[j] ^= key[j];
			}

			while (!block.empty() && block.back() == 0x81)
			{
				block.pop_back();
			}

			output.insert(output.end(), block.begin(), block.end());
			blockStart += key.size();
		}
	}

	return output;
}

vector<char> processStreamCipher(const vector<char> &input, const vector<char> &key)
{
	vector<char> output;
	size_t i = 0;
	for (auto c : input)
	{
		output.push_back(c ^ key[i]);
		i = (i + 1) % key.size();
	}

	return output;
}
