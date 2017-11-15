/*
	This is a collection of helper functions for the Project 3 - BMP Reader/Writer
*/

#include "Helper.h"

// read a number from some amount of bytes in Little Endian
int Helper::getNumber(const char* bmpFile, int index, int range)
{
	//char numTest[4] = { '\x0020', '\x0003', '\x0000', '\x0000' };
	//unsigned int* intTest = reinterpret_cast<unsigned int*>(numTest);

	//std::cout << *intTest << ", " << sizeof(intTest) << std::endl;
	//
	//system("pause");
	
	char* val = new char[range];
	for (int i = 0; i < range; i++)
	{
		val[i] = bmpFile[index + i];
	}
	unsigned int* returnValP = reinterpret_cast<unsigned int*>(val);
	delete[] val;
	unsigned int returnVal = *returnValP;
	return returnVal;
}

// input a string
void Helper::write(std::ofstream& fout, std::string input, int size)
{
	//convert input to char*
	char* cinput = new char[size];
	for (int i = 0; i < size; i++)
	{
		char c; 
		c = input.c_str()[i];
		if (c == '\0')	// we don't want the null terminator at the end of a c-string
			break;
		cinput[i] = c;
	}
	//write to fout
	fout.write(switchEndianness(cinput, size), size);
	//move the stream pointer to the next read position
	//fout.seekp(fout.tellp(), size);
	delete[] cinput;
}

// input a char *
void Helper::write(std::ofstream& fout, char* input, int size)
{
	//write to fout
	fout.write(switchEndianness(input, size), size);
	//move the stream pointer to the next read position
	//fout.seekp(fout.tellp(), size);
}

// input a char
void Helper::write(std::ofstream& fout, char input, int size)
{
	char cinput[] = { input };
	//write to fout
	fout.write(cinput, size);
	//move the stream pointer to the next read position
	//fout.seekp(fout.tellp(), size);
}

// input an int
void Helper::write(std::ofstream& fout, int input, int size)
{
	char* cinput = reinterpret_cast<char *>(&input);
	//write to fout
	fout.write(switchEndianness(cinput, size), size);
	//move the stream pointer to the next read position
	//fout.seekp(fout.tellp(), size);
}

// flip a char*
char* Helper::switchEndianness(char* input, int size)
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