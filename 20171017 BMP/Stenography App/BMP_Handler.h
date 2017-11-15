#pragma once

#ifdef BMPEXPORTS
#define BMP_API __declspec(dllexport)
#else
#define BMP_API __declspec(dllimport)
#pragma comment(lib, "BMP_Handler32d.lib")
#endif

class BMP_Handler {
public:
	static BMP_API unsigned char* loadBMP(const char*, int&, int&);

	static BMP_API void saveBMP(const char*, const unsigned char*, int, int);
};