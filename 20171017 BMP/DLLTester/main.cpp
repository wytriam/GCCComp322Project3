#include <BMP_Handler.h>
#include <cstdlib>

int main(int argc, char** argv)
{
	BMP_Handler bmp;
	int width, height;
	bmp.loadBMP("experiment.bmp", width, height);

	system("pause");

	return 0;
}