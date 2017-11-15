#include <BMP_Handler.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	BMP_Handler;
	int width, height;
	unsigned char* test;
	test = BMP_Handler::loadBMP("test4.bmp", width, height);	
	BMP_Handler::saveBMP("t4.bmp", test, width, height);

	return 0;
}