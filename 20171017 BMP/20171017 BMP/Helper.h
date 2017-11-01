#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Helper
{
public:
	static int getNumber(const char*, int, int);
	static void write(std::ofstream&, std::string, int);
	static void write(std::ofstream&, char*, int);
	static void write(std::ofstream&, char, int);
	static char* toLittleEndian(char*, int);
};