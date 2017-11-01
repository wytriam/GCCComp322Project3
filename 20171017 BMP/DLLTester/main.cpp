#include <BMP_Handler.h>
#include <cstdlib>

int main(int argc, char** argv)
{
	BMP_Handler;
	int width, height;
	unsigned char* test;
	test = BMP_Handler::loadBMP("secretmessage1.bmp", width, height);
	BMP_Handler::saveBMP("sm1.bmp", test, width, height);

	system("pause");

	return 0;
}