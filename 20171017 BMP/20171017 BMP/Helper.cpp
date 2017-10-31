#include "Helper.h"

int Helper::getNumber(const char* bmpFile, int index, int range)
{
	std::string val = "";
	for (int i = index + range - 1; i >= index; i--)
	{
		val += bmpFile[i];
	}
	return atoi(val.c_str());
}

void Helper::write(std::ofstream& fout, std::string input, int size)
{
	//convert input to char*
	char* cinput = new char[size];
	for (int i = 0; i < size; i++)
	{
		char c; 
		c = input.c_str()[i];
		if (c == '\0')
			break;
		cinput[i] = c;
	}
	//write to fout
	fout.write(toLittleEndian(cinput, size), size);
	//move the stream pointer to the next read position
	fout.seekp(fout.tellp, size);
	delete[] cinput;
}

void Helper::write(std::ofstream& fout, char* input, int size)
{
	//write to fout
	fout.write(toLittleEndian(input, size), size);
	//move the stream pointer to the next read position
	fout.seekp(fout.tellp, size);
}

char* Helper::toLittleEndian(char* input, int size)
{
	// Adapted from http://www.cplusplus.com/forum/beginner/189483/
	for (int i = 0; i < (size / 2); i++) 
	{
		char temp = input[i];                 
		input[i] = input[(size - 1) - i];
		input[(size - 1) - i] = temp;
	}
	return input;
}