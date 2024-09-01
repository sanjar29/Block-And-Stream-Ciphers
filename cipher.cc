#include "cipher.h"
using namespace std;

vector<char> processBlockCipher(const vector<char> &input_data, const vector<char> &key_data, char operation_mode)
{
	vector<char> result_data;
	if (operation_mode == 'E')
		for (size_t block_start = 0; block_start < input_data.size(); block_start += key_data.size())
		{
			vector<char> block(input_data.begin() + block_start, input_data.begin() + min(block_start + key_data.size(), input_data.size()));
			if (block.size() < key_data.size())
				for (size_t i = block.size(); i < key_data.size(); i++)
					block.push_back(0x81);
			for (size_t j = 0; j < block.size(); j++)
				block[j] ^= key_data[j];
			vector<char>::iterator start = block.begin();
			vector<char>::iterator end = block.end() - 1;
			while (start < end)
				for (char byte : key_data)
				{
					if (byte % 2)
					{
						iter_swap(start, end);
						end = end - 1;
					}
					start = start + 1;
					if (start >= end)
						break;
				}
			result_data.insert(result_data.end(), block.begin(), block.end());
		}

	else if (operation_mode == 'D')
	{
		for (size_t block_start = 0; block_start < input_data.size(); block_start += key_data.size())
		{
			vector<char> block(input_data.begin() + block_start, input_data.begin() + min(block_start + key_data.size(), input_data.size()));
			vector<char>::iterator start = block.end() - 1;
			vector<char>::iterator end = block.begin();
			while (start > end)
				for (char byte : key_data)
				{
					if (byte % 2)
					{
						iter_swap(start, end);
						start = start - 1;
					}
					end = end + 1;
					if (start <= end)
						break;
				}
			for (size_t j = 0; j < block.size(); j++)
				block[j] ^= key_data[j];
			while (!block.empty() && block.back() == 0x81)
				block.pop_back();
			result_data.insert(result_data.end(), block.begin(), block.end());
		}
	}
	return result_data;
}
void argumentValidation(int arg_count, char *args[])
{
	if (arg_count != 6)
		throw runtime_error("Incorrect number of arguments");
	if (args[1][0] != 'B' && args[1][0] != 'S')
		throw runtime_error("First argument must be 'B' or 'S'");
	if (args[5][0] != 'E' && args[5][0] != 'D')
		throw runtime_error("Fifth argument must be 'E' or 'D'");
}
int main(int arg_count, char *args[])
{
	try
	{
		argumentValidation(arg_count, args);
		char func_type = args[1][0];
		char operation_mode = args[5][0];
		vector<char> input_data = readFile(args[2]);
		vector<char> key_data = readFile(args[4]);
		vector<char> result_data;
		if (input_data.empty())
			writeFile(args[3], result_data);
		if (func_type == 'B')
			result_data = processBlockCipher(input_data, key_data, operation_mode);
		else if (func_type == 'S')
			result_data = processStreamCipher(input_data, key_data);
		writeFile(args[3], result_data);
	}
	catch (const exception &err)
	{
		cerr << "Error: " << err.what() << endl;
		return 1;
	}
	return 0;
}

vector<char> readFile(const string &filename)
{
	ifstream file_stream(filename, ios::binary);
	if (!file_stream)
		throw runtime_error("File " + filename + " not found");
	return vector<char>((istreambuf_iterator<char>(file_stream)), istreambuf_iterator<char>());
}

void writeFile(const string &filename, const vector<char> &data)
{
	ofstream file_stream(filename, ios::binary);
	if (!file_stream)
		throw runtime_error("Unable to open file " + filename);
	file_stream.write(data.data(), data.size());
}
vector<char> processStreamCipher(const vector<char> &input_data, const vector<char> &key_data)
{
	vector<char> result_data;
	size_t key_index = 0;
	for (auto c : input_data)
	{
		result_data.push_back(c ^ key_data[key_index]);
		key_index = (key_index + 1) % key_data.size();
	}
	return result_data;
}
