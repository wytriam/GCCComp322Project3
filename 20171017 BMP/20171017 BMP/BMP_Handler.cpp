#include "BMP_Handler.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <string>

#include "Helper.h"

unsigned char* BMP_Handler::loadBMP(const char* filename, int& width, int& height)
{
	// create an array to return
	unsigned char* rgbVals;

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

		// The BITMAPFILEHEADER struct is 14 bytes long, so bmpFile[14] should be the start of the BITMAPV5HEADER
		// bmpFile[19] should be the start of the height long
		// bmpFile[23] should be the start of the width long
		width = Helper.getNumber(bmpFile, 19, 4);
		height = Helper.getNumber(bmpFile, 23, 4);

		// initialize rgbVals
		int size = width*height;
		rgbVals = new unsigned char[size];
		
		// read the pixel array, populate rgbVals
		// pixel array should start at 54 (14 for BITMAPFILEHEADER, 40 for BITMAPV5HEADER)
		for (int i = 0; i < size; i++)
			rgbVals[i] = bmpFile[i + 54];

		delete[] bmpFile;
	}

	return rgbVals;

}

void BMP_Handler::saveBMP(const char* filename, const unsigned char* RGBvals, int width, int height)
{
	std::ofstream fout(filename, std::ios::binary | std::ios::out | std::ios::trunc);
	if (fout.is_open())
	{
		std::string signature = "BM";
		fout.write(signature.c_str(), 2);
	}
}