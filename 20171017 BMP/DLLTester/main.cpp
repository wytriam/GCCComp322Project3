#include <BMP_Handler.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	BMP_Handler;
	int width, height;
	unsigned char* test;
	test = BMP_Handler::loadBMP("test2.bmp", width, height);	
	BMP_Handler::saveBMP("t2.bmp", test, width, height);
	delete[] test;

	return 0;
}