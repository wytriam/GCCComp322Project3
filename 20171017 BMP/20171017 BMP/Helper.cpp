/*
	This is a collection of helper functions for the Project 3 - BMP Reader/Writer
*/

#include "Helper.h"

// read a number from some amount of bytes in Little Endian
int Helper::getNumber(const char* bmpFile, int index, int range)
{
	char val[4] = {};
	for (int i = 0; i < 4; i++)
	{
		val[i] = bmpFile[index + i];
	}
	unsigned int* returnVal = reinterpret_cast<unsigned int*>(val);
	return *returnVal;
}

// input a char *
void Helper::write(std::ofstream& fout, char* input, int size)
{
	//write to fout
	fout.write(input, size);
}

// input a char
void Helper::write(std::ofstream& fout, char input, int size)
{
	// put the input in an array for the write function
	char cinput[] = { input };
	//write to fout
	fout.write(cinput, size);
}

// input an int
void Helper::write(std::ofstream& fout, int input, int size)
{
	char* cinput = reinterpret_cast<char *>(&input);
	//write to fout
	fout.write(cinput, size);
}