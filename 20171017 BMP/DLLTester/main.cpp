/*
	This is a derpy little stub class to let me test things the BMP_Handler class. Lots of breakpoints that have now been removed. 
*/

#include <BMP_Handler.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	BMP_Handler;
	int width, height;
	unsigned char* test;
	test = BMP_Handler::loadBMP("test2.bmp", width, height);	
	BMP_Handler::saveBMP("test2f.bmp", test, width, height);

	return 0;
}