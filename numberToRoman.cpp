#include "numberToRoman.hpp"

std::string numberToRoman(const int x)
{
	//assert(x < 5000);

	std::string result;
	int val = x;

    int tmp = val / 1000;
	for(int i = 0; i < tmp; i++)
	{
		result.append("M");
		val -= 1000;
	}

	if (val / 900 > 0)
	{
		result.append("CM");
		val -= 900;
	}

	if (val / 500 > 0)
	{
		result.append("D");
		val -= 500;
	}

	if (val / 400 > 0)
	{
		result.append("CD");
		val -= 400;
	}

    tmp = val / 100;
	for(int i = 0; i < tmp; i++)
	{
		result.append("C");
		val -= 100;
	}

	if (val / 90 > 0)
	{
		result.append("XC");
		val -= 90;
	}

	if (val / 50 > 0)
	{
		result.append("L");
		val -= 50;
	}

	if (val / 40 > 0)
	{
		result.append("XL");
		val -= 40;
	}

    tmp = val / 10;
	for(int i = 0; i < tmp; i++)
	{
		result.append("X");
		val -= 10;
	}

	if (val / 9 > 0)
	{
		result.append("IX");
		val -= 9;
	}

	if (val / 5 > 0)
	{
		result.append("V");
		val -= 5;
	}

	if (val / 4 > 0)
	{
		result.append("IV");
		val -= 4;
	}

	for(int i = 0; i < val; i++)
		result.append("I");

	return result;
}
