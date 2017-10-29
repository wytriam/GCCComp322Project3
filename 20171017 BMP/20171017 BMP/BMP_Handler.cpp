#include "BMP_Handler.h"
#include <fstream>
#include <iostream>
#include <assert.h>

unsigned char* BMP_Handler::loadBMP(const char* filename, int& width, int& height)
{
	// create an array to return
	unsigned char rgbVals [5];

	std::streampos size;
	char * bmpFile;

	// open the file in binary mode
	std::ifstream fin;
	fin.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
	// if the file is open...
	if (fin.is_open())
	{
		// put file into memory
		// adapted from http://www.cplusplus.com/doc/tutorial/files/

		size = fin.tellg();
		bmpFile = new char[size];
		fin.seekg(0, std::ios::beg);
		fin.read(bmpFile, size);
		fin.close();

		// check the file signature (make sure this is .bmp). Signature should be BM (01000010 01001101 in ASCII)
		// 1 char = 1 byte
		if (!(bmpFile[0] == 'B' && bmpFile[1] == 'M'))
		{
			throw "File does not begin with BM. Either not a bitmap file or not file is corrupted.";
		}

		// read past the BITMAP FILE HEADER
		// open up BITMAPV5HEADER
		// read and save width
		// read and save height
		// initialize bmp
		// ignore a bunch of other stuff I don't want to understand
		// read the pixel array, populate bmp

		delete[] bmpFile;
	}

	return rgbVals;
}

void BMP_Handler::saveBMP(const char* filename, const unsigned char* RGBvals, int width, int height)
{

}