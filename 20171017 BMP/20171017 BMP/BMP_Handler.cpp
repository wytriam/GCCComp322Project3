#include "BMP_Handler.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>

#include "Helper.h"

unsigned char* BMP_Handler::loadBMP(const char* filename, int& width, int& height)
{
	assert(1 == 0);
	// create an array to return
	unsigned char* rgbVals = NULL;
	assert(2 == 0);
	std::streampos size;
	assert(3 == 0);
	char * bmpFile;
	assert(4 == 0);
	// open the file in binary mode
	std::ifstream fin;
	assert(5 == 0);
	fin.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
	assert(6 == 0);
	// if the file is open...
	if (fin.is_open())
	{
		assert(7 == 0);
		// put file into memory
		// adapted from http://www.cplusplus.com/doc/tutorial/files/

		size = fin.tellg();
		assert(8 == 0);
		bmpFile = new char[size];
		assert(9 == 0);
		fin.seekg(0, std::ios::beg);
		assert(10 == 0);
		fin.read(bmpFile, size);
		assert(11 == 0);
		fin.close();
		assert(12 == 0);

		// check the file signature (make sure this is .bmp). Signature should be BM (01000010 01001101 in ASCII)
		// 1 char = 1 byte
		if (!(bmpFile[0] == 'B' && bmpFile[1] == 'M'))
		{
			assert(13 == 0);
			throw "File does not begin with BM. Either not a bitmap file or not file is corrupted.";
		}

		// The BITMAPFILEHEADER struct is 14 bytes long, so bmpFile[14] should be the start of the BITMAPV5HEADER
		// bmpFile[19] should be the start of the height long
		// bmpFile[23] should be the start of the width long
		width = Helper::getNumber(bmpFile, 19, 4);
		assert(14 == 0);
		height = Helper::getNumber(bmpFile, 23, 4);
		assert(15 == 0);

		// calculate necessary padding
		int padding = 4 - ((width * 3) % 4);
		assert(16 == 0);
		if (padding == 4)
			padding = 0;
		assert(17 == 0);

		// initialize rgbVals
		int RGBsize = ((width*3) + padding ) * height;
		assert(18 == 0);
		rgbVals = new unsigned char[RGBsize];
		assert(19 == 0);
		
		// read the pixel array, populate rgbVals
		// pixel array should start at 54 (14 for BITMAPFILEHEADER, 40 for BITMAPV5HEADER)
		int offset = Helper::getNumber(bmpFile, 11, 4);
		assert(20 == 0);
		// loop over everything, skipping over the padding
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < (width * 3); j++)
			{
				rgbVals[(i*height) + j] = bmpFile[offset + ((i*height) + j)];
			}
		}
		assert(21 == 0);
		delete[] bmpFile;
		assert(22 == 0);
	}
	return rgbVals;
}

void BMP_Handler::saveBMP(const char* filename, const unsigned char* RGBvals, int width, int height)
{	
	assert(2 == 1);
	std::ofstream fout(filename, std::ios::binary | std::ios::out | std::ios::trunc);
	if (fout.is_open())
	{
		// calculate necessary padding
		int padding = 4 - ((width * 3) % 4);
		if (padding == 4)
			padding = 0;
		
		// set up some variables to be used in writing
		char emptyWord[] = { '\0', '\0' };
		char emptyDWord[] = { '\0', '\0', '\0', '\0' };

		// BITMAPFILEHEADER - https://msdn.microsoft.com/en-us/library/windows/desktop/dd183374(v=vs.85).aspx
		// bfType - The file type; must be BM
		Helper::write(fout, 'B', 1);
		Helper::write(fout, 'M', 1);
		// bfSize - The size, in bytes, of the bitmap file
		int size = 54 + (((width * 3) + padding) * height);
		Helper::write(fout, size, 4);
		// bfReserved1 - Reserved, must be zero
		Helper::write(fout, emptyDWord, 4);
		// bfReserved2 - Reserved; must be zero
		Helper::write(fout, emptyDWord, 4);
		// bfOffBits - The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits
		int offset = 54;
		Helper::write(fout, offset, 4);

		// BITMAPV5HEADER - https://msdn.microsoft.com/en-us/library/windows/desktop/dd183381(v=vs.85).aspx
		// bV5Size - The number of bytes required by the structure. Applications should use this member to determine which bitmap information header structure is being used.
		// should be 40
		int bV5Size = 40;
		Helper::write(fout, bV5Size, 4);
		// bV5Width - The width of the bitmap, in pixels.
		Helper::write(fout, width, 4);
		// bV5Height - The height of the bitmap, in pixels. 
		Helper::write(fout, height, 4);
		// bV5Planes - The number of planes for the target device. This value must be set to 1.
		Helper::write(fout, 1, 2);
		// bV5BitCount - The number of bits that define each pixel and the maximum number of colors in the bitmap. 
			// Value - 24. Meaning: The bitmap has a maximum of 2^24 colors, and the bmiColors member of BITMAPINFO is NULL.
			// Each 3-byte triplet in the bitmap array represents the relative intensites of blue, green, and red, respecitively
			// for a pixel. The bmiColors color table is used for optimizing colors used on palette-based devices, and 
			// must contain the number of entried specifed by the bV5ClrUsed member of the BITMAPV5HEADER structure
		Helper::write(fout, 24, 2);
		// bV5Compression - Specifies that the bitmap is not compressed. BI_RGB is an uncompressed format.
		Helper::write(fout, emptyDWord, 4);
		// bV5SizeImage - The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps
		Helper::write(fout, emptyDWord, 4);
		// bV5XPelsPerMeter - The horizontal resolution, in pixels-per-meter, of the target device for the bitmap
		Helper::write(fout, emptyDWord, 4);
		// bV5YPelsPerMeter - The vertical resolution, in pixels-per-meter, of the target device for the bitmap
		Helper::write(fout, emptyDWord, 4);
		// bV5ClrUsed - The number of color indexes in the color that are actually used by the bitmap. If this value is zero, the bitmap uses the maximum number of colors corresponding to the value of the bV5BitCount member for the compression mode specified by bV5Compression
		Helper::write(fout, emptyDWord, 4);
		// bV5ClrImportant - The number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required
		Helper::write(fout, emptyDWord, 4);
		// Pixel Data
		for (int i = 0; i < height; i++)
		{
			// add pixel data
			for (int j = 0; j < width; j++)
				Helper::write(fout, RGBvals[height*i + width], 1);
			// add padding if necessary
			for (int j = 0; j < padding; j++)
				Helper::write(fout, '\0', 1);
		}
	}

	fout.close();
}