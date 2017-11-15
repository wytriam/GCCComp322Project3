#include <BMP_Handler.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	char* numTest;// = { '\x0020', '\x0003', '\x0000', '\x0000' };
	int size = 4;
	numTest = new char[size];
	numTest[0] = '\x0020';
	numTest[1] = '\x0003';
	numTest[2] = '\x0000';
	numTest[3] = '\x0000';
	unsigned int* intTest = reinterpret_cast<unsigned int*>(numTest);

	std::cout << *intTest << ", " << sizeof(intTest) << std::endl;
	
	system("pause");

	BMP_Handler;
	int width, height;
	unsigned char* test;
	test = BMP_Handler::loadBMP("secretmessage1.bmp", width, height);
	system("pause");
	
	std::cout << sizeof(1) << std::endl;
	
	//BMP_Handler::saveBMP("sm1.bmp", test, width, height);

	system("pause");

	return 0;
}