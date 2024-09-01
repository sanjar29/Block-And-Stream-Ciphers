#include "cipher.h"

using namespace std;

vector<char> stream_cipher_input_validator(const vector<char> &input, const vector<char> &key)
{
	vector<char> output;
	size_t keyIndex = 0;
	for (char byte : input)
	{
		output.push_back(byte ^ key[keyIndex]);
		keyIndex = (keyIndex + 1) % key.size();
	}
	return output;
}

void checkArgumentCorrectness(int argc, char *argv[])
{
	if (argc != 6)
		throw runtime_error("Invalid Number of Arguments");
	if (argv[1][0] != 'B' && argv[1][0] != 'S')
		throw runtime_error("Invalid Function Type");
	if (argv[5][0] != 'E' && argv[5][0] != 'D')
		throw runtime_error("Invalid Mode Type");
}

void output_to_the_file(const string &filename, const vector<char> &data)
{
	ofstream file(filename, ios::binary);
	if (!file)
		throw runtime_error("Output File Could Not Be Created");
	file.write(data.data(), data.size());
}
int main(int argc, char *argv[])
{
	try
	{
		checkArgumentCorrectness(argc, argv);
		char functionType = argv[1][0];
		char mode = argv[5][0];
		vector<char> input = reading_file(argv[2]);
		vector<char> key = reading_file(argv[4]);
		vector<char> output;
		if (input.empty())
		{
			output_to_the_file(argv[3], output);
			return 0;
		}
		if (functionType == 'B')
			output = bloc_cipher_input_validator(input, key, mode);
		else if (functionType == 'S')
			output = stream_cipher_input_validator(input, key);
		output_to_the_file(argv[3], output);
	}
	catch (const exception &e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	return 0;
}

vector<char> bloc_cipher_input_validator(const vector<char> &input, const vector<char> &key, char mode)
{
	vector<char> result;
	const size_t BLOCK_SIZE = 16;
	const char PAD_BYTE = 0x81;
	if (mode == 'E')
		for (size_t blockStart = 0; blockStart < input.size(); blockStart += BLOCK_SIZE)
		{
			vector<char> block(input.begin() + blockStart, input.begin() + min(blockStart + BLOCK_SIZE, input.size()));
			if (block.size() < BLOCK_SIZE)
				block.resize(BLOCK_SIZE, PAD_BYTE);
			for (size_t j = 0; j < block.size(); ++j)
				block[j] ^= key[j];
			size_t start = 0;
			size_t end = block.size() - 1;
			while (start < end)
				for (char byte : key)
				{
					if (byte % 2)
					{
						swap(block[start], block[end]);
						--end;
					}
					++start;
					if (start >= end)
						break;
				}
			result.insert(result.end(), block.begin(), block.end());
		}
	else if (mode == 'D')
		for (size_t blockStart = 0; blockStart < input.size(); blockStart += BLOCK_SIZE)
		{
			vector<char> block(input.begin() + blockStart, input.begin() + min(blockStart + BLOCK_SIZE, input.size()));
			size_t start = block.size() - 1;
			size_t end = 0;
			while (start > end)
				for (char byte : key)
				{
					if (byte % 2)
					{
						swap(block[start], block[end]);
						--start;
					}
					++end;
					if (start <= end)
						break;
				}
			for (size_t j = 0; j < block.size(); ++j)
				block[j] ^= key[j];
			while (!block.empty() && block.back() == PAD_BYTE)
				block.pop_back();
			result.insert(result.end(), block.begin(), block.end());
		}
	return result;
}
vector<char> reading_file(const string &filename)
{
	ifstream file(filename, ios::binary);
	if (!file)
		throw runtime_error("Input File Does Not Exist");
	return vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}
