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
		width = Helper::getNumber(bmpFile, 19, 4);
		height = Helper::getNumber(bmpFile, 23, 4);

		// initialize rgbVals
		int size = width*height;
		rgbVals = new unsigned char[size];
		
		// read the pixel array, populate rgbVals
		// pixel array should start at 54 (14 for BITMAPFILEHEADER, 40 for BITMAPV5HEADER)
		int offset = Helper::getNumber(bmpFile, 11, 4);
		for (int i = 0; i < size; i++)
			rgbVals[i] = bmpFile[i + offset];

		delete[] bmpFile;
	}

	return rgbVals;

}

void BMP_Handler::saveBMP(const char* filename, const unsigned char* RGBvals, int width, int height)
{	
	std::ofstream fout(filename, std::ios::binary | std::ios::out | std::ios::trunc);
	if (fout.is_open())
	{
		// calculate necessary padding
		int padding = 4 - ((width * 3) % 4);
		if (padding == 4)
			padding = 0;
		
		char emptyWord[] = { '\0', '\0' };
		char* forItoA = new char[sizeof(int) * 8 + 1];


		// BITMAPFILEHEADER - https://msdn.microsoft.com/en-us/library/windows/desktop/dd183374(v=vs.85).aspx
		// bfType - The file type; must be BM
		Helper::write(fout, "B", 1);
		Helper::write(fout, "M", 1);
		// bfSize - The size, in bytes, of the bitmap file
		int size = 54 + (((width * 3) + padding) * height);
		Helper::write(fout, itoa(size, forItoA, 10), 4);
		// bfReserved1 - Reserved, must be zero
		// bfReserved2 - Reserved; must be zero
		for (int i = 0; i < 4; i++)
			Helper::write(fout, emptyWord, 2);
		// bfOffBits - The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits
		int offset = 54;
		Helper::write(fout, itoa(offset, forItoA, 10), 4);

		// BITMAPV5HEADER - https://msdn.microsoft.com/en-us/library/windows/desktop/dd183381(v=vs.85).aspx
		// bV5Size - The number of bytes required by the structure. Applications should use this member to determine which bitmap information header structure is being used.
		// bV5Width - The width of the bitmap, in pixels.
		// bV5Height - The height of the bitmap, in pixels. 
		// bV5Planes - The number of planes for the target device. This value must be set to 1.
		// bV5BitCount - The number of bits that define each pixel and the maximum number of colors in the bitmap. 
			// Value - 24. Meaning: The bitmap has a maximum of 2^24 colors, and the bmiColors member of BITMAPINFO is NULL.
			// Each 3-byte triplet in the bitmap array represents the relative intensites of blue, green, and red, respecitively
			// for a pixel. The bmiColors color table is used for optimizing colors used on palette-based devices, and 
			// must contain the number of entried specifed by the bV5ClrUsed member of the BITMAPV5HEADER structure
		// bV5Compression - Specifies that the bitmap is not compressed. BI_RGB is an uncompressed format.
		// bV5SizeImage - The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps
		// bV5XPelsPerMeter - The horizontal resolution, in pixels-per-meter, of the target device for the bitmap
		// bV5YPelsPerMeter - The vertical resolution, in pixels-per-meter, of the target device for the bitmap
		// bV5ClrUsed - The number of color indexes in the color that are actually used by the bitmap. If this value is zero, the bitmap uses the maximum number of colors corresponding to the value of the bV5BitCount member for the compression mode specified by bV5Compression
		// bV5ClrImportant - The number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required
		// Pixel Data

		delete[] forItoA;
	}

	fout.close();
}