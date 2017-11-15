#include <BMP_Handler.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	BMP_Handler;
	int width, height;
	unsigned char* test;
	test = BMP_Handler::loadBMP("secretmessage1.bmp", width, height);	
	BMP_Handler::saveBMP("sm1.bmp", test, width, height);

	return 0;
}