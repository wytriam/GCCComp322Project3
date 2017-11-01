#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

class Helper
{
public:
	static int getNumber(const char*, int, int);
	static void write(std::ofstream&, std::string, int);
	static void write(std::ofstream&, char*, int);
	static void write(std::ofstream&, char, int);
	static void write(std::ofstream&, int, int);
	static char* toLittleEndian(char*, int);
};