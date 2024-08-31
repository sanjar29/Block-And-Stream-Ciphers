#include "cipher.h"
using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		argument_validity(argc, argv);
		char stream_or_block = argv[1][0];
		char mode = argv[5][0];
		vector<char> input_file = file_reader(argv[2]);
		vector<char> key_file = file_reader(argv[4]);
		vector<char> output_file;

		if (input_file.empty())
		{
			writer_to_the_output_file(argv[3], output_file);
			return 0;
		}
		if (stream_or_block == 'B')
		{
			output_file = block_cipher_function(input_file, key_file, mode);
		}
		else if (stream_or_block == 'S')
		{
			output_file = stream_cipher_function(input_file, key_file);
		}
		writer_to_the_output_file(argv[3], output_file);
	}
	catch (const exception &exc)
	{
		cerr << "Error: " << exc.what() << endl;
		return 1;
	}
	return 0;
}

void argument_validity(int argc, char *argv[])
{
	if (argc != 6)
		throw runtime_error("Wrong number of arguments provided");
	if (argv[1][0] != 'S' && argv[1][0] != 'B')
		throw runtime_error("Invalid Function Type");
	if (argv[5][0] != 'D' && argv[5][0] != 'E')
		throw runtime_error("Invalid Mode Type");
}

vector<char> file_reader(const string &input_file)
{
	ifstream file(input_file, ios::binary);
	if (!file)
		throw runtime_error(input_file + " File Does Not Exist");
	return vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

void writer_to_the_output_file(const string &input_file, const vector<char> &info)
{
	ofstream file(input_file, ios::binary);
	if (!file)
		throw runtime_error("");
	file.write(info.data(), info.size());
}

vector<char> block_cipher_function(const vector<char> &input_file, const vector<char> &key_file, char mode)
{
	vector<char> output_file;
	if (mode == 'E')
	{
		size_t beginning_of_the_block = 0;
		while (beginning_of_the_block < input_file.size())
		{
			vector<char> block(input_file.begin() + beginning_of_the_block, input_file.begin() + min(beginning_of_the_block + key_file.size(), input_file.size()));
			if (block.size() < key_file.size())
			{
				for (size_t i = block.size(); i < key_file.size(); i++)
				{
					block.push_back(0x81);
				}
			}

			for (size_t j = 0; j < block.size(); j++)
			{
				block[j] ^= key_file[j];
			}

			vector<char>::iterator beginning = block.begin();
			vector<char>::iterator end = block.end() - 1;
			while (beginning < end)
			{
				for (char byte : key_file)
				{
					bool swap = byte % 2;
					if (swap)
					{
						iter_swap(beginning, end);
						end = end - 1;
					}
					beginning = beginning + 1;
					if (beginning >= end)
						break;
				}
			}
			output_file.insert(output_file.end(), block.begin(), block.end());
			beginning_of_the_block += key_file.size();
		}
	}
	else if (mode == 'D')
	{
		size_t beginning_of_the_block = 0;
		while (beginning_of_the_block < input_file.size())
		{
			vector<char> block(input_file.begin() + beginning_of_the_block, input_file.begin() + min(beginning_of_the_block + key_file.size(), input_file.size()));
			vector<char>::iterator beginning = block.end() - 1;
			vector<char>::iterator end = block.begin();
			while (beginning > end)
			{
				for (char byte : key_file)
				{
					bool swap = byte % 2;
					if (swap)
					{
						iter_swap(beginning, end);
						beginning = beginning - 1;
					}
					end = end + 1;
					if (beginning <= end)
						break;
				}
			}

			for (size_t j = 0; j < block.size(); j++)
				block[j] ^= key_file[j];
			while (!block.empty() && block.back() == 0x81)
				block.pop_back();

			output_file.insert(output_file.end(), block.begin(), block.end());
			beginning_of_the_block += key_file.size();
		}
	}
	return output_file;
}

vector<char> stream_cipher_function(const vector<char> &input_file, const vector<char> &key_file)
{
	vector<char> output_file;
	size_t index_start = 0;
	for (auto character : input_file)
	{
		output_file.push_back(character ^ key_file[index_start]);
		index_start = (index_start + 1) % key_file.size();
	}
	return output_file;
}
