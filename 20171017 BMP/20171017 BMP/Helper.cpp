#include "Helper.h"

int Helper::getNumber(const char* bmpFile, int index, int range)
{
	std::string val = "";
	for (int i = index + range - 1; i >= index; i--)
	{
		val += bmpFile[i];
	}
	return atoi(val.c_str());
}