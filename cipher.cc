#include "cipher.h"
using namespace std;

void validateInputs(int argc, char *argv[])
{
	if (argc != 6)
		throw runtime_error("Invalid argument count");
	if (argv[1][0] != 'B' && argv[1][0] != 'S')
		throw runtime_error("Invalid cipher type");
	if (argv[5][0] != 'E' && argv[5][0] != 'D')
		throw runtime_error("Invalid operation mode");
}
vector<char> readData(const string &filename)
{
	ifstream fileStream(filename, ios::binary);
	if (!fileStream)
		throw runtime_error("Cannot open file " + filename);
	return vector<char>((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
}
int main(int argc, char *argv[])
{
	try
	{
		validateInputs(argc, argv);
		char cipherType = argv[1][0];
		char operationMode = argv[5][0];
		vector<char> data = readData(argv[2]);
		vector<char> key = readData(argv[4]);
		vector<char> result;
		if (data.empty())
		{
			saveData(argv[3], result);
			return 0;
		}
		if (cipherType == 'B')
			result = executeBlockCipher(data, key, operationMode);
		else if (cipherType == 'S')
			result = executeStreamCipher(data, key);
		saveData(argv[3], result);
	}
	catch (const exception &e)
	{
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	return 0;
}
void saveData(const string &filename, const vector<char> &data)
{
	ofstream fileStream(filename, ios::binary);
	if (!fileStream)
		throw runtime_error("Failed to open file " + filename);
	fileStream.write(data.data(), data.size());
}
vector<char> executeStreamCipher(const vector<char> &data, const vector<char> &key)
{
	vector<char> result;
	size_t keyIndex = 0;
	for (char byte : data)
	{
		result.push_back(byte ^ key[keyIndex]);
		keyIndex = (keyIndex + 1) % key.size();
	}
	return result;
}
vector<char> executeBlockCipher(const vector<char> &data, const vector<char> &key, char mode)
{
	vector<char> result;
	size_t blockOffset = 0;
	while (blockOffset < data.size())
	{
		vector<char> block(data.begin() + blockOffset, data.begin() + min(blockOffset + key.size(), data.size()));
		if (mode == 'E')
		{
			if (block.size() < key.size())
				block.resize(key.size(), 0x81);
			for (size_t i = 0; i < block.size(); ++i)
				block[i] ^= key[i];
			reverseBlockWithKey(block, key);
		}
		else if (mode == 'D')
		{
			reverseBlockWithKey(block, key);
			for (size_t i = 0; i < block.size(); ++i)
				block[i] ^= key[i];
			while (!block.empty() && block.back() == 0x81)
				block.pop_back();
		}
		result.insert(result.end(), block.begin(), block.end());
		blockOffset += key.size();
	}
	return result;
}

void reverseBlockWithKey(vector<char> &block, const vector<char> &key)
{
	auto start = block.begin();
	auto end = block.end() - 1;
	while (start < end)
	{
		for (char k : key)
		{
			bool swap = k % 2;
			if (swap)
			{
				iter_swap(start, end);
				end = end - 1;
			}
			start = start + 1;
			if (start >= end)
				break;
		}
	}
}