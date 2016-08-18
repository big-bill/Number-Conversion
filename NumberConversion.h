/*
This class handles the conversion of numeric numbers to their English equivalent word. 
Can only go up to 10,000.
Made by Billy Matthews, Feb. 2016
*/

#ifndef NUMBERCONVERSION_H
#define NUMBERCONVERSION_H
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <iostream>

class NumberConversion
{
private:
	std::vector<std::string> ones;
	std::vector<std::string> teens;
	std::vector<std::string> tens;

	//this string holds the converted number
	std::string convertedNumber;
	bool testTens;
	int digit;


public:
	NumberConversion();
	void convertNumber(char*, int);

	void findDigitName();
	void findTensName();


	//this will take in a float and return the decimal place value
	//it's named "getCentsValue" because it doesn't just return the decimal place,
	//it returns the proper value if the number is .06, the string return will be "6" instead of "06"
	//check the function for why I did it this way
	std::string getCentsValue(float);

	std::string getConvertedNumber(){ return convertedNumber; }
};

#endif