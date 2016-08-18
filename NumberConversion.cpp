#include "NumberConversion.h"

//-------------------------------------------------------------------------------------------------------------------------------
NumberConversion::NumberConversion()
{
	//initialization of variables
	convertedNumber = "";
	testTens = false;
	digit = 0;
	ones =
	{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	teens =
	{ "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	tens =
	{ "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety" };

}

//-------------------------------------------------------------------------------------------------------------------------------
void NumberConversion::convertNumber(char* paymentChar, int paymentInt)
{
	convertedNumber.clear();
	bool continueProgram = false;
	//handles the values between 1-19 and 10000
	if ((paymentInt >= 0 && paymentInt <= 19) || paymentInt == 10000)
	{
		if (paymentInt < 1.0 && paymentInt >= 0.0)
			convertedNumber.append("zero");
		else if (paymentInt <= 9)
			convertedNumber.append(ones[paymentInt - 1]);
		else if (paymentInt != 10000)
			convertedNumber.append(teens[paymentInt - 10]);
		else
			convertedNumber.append("ten thousand");

		convertedNumber.append(" "); //adds a space
		continueProgram = true; //temporarily used to test whether or not the value has been converted
		//if not, resume the conversion 
	}

	if (!continueProgram)
	{
		for (int count = 0; count < (int)strlen(paymentChar); count++)
		{
			testTens = false;

			//gets the digit value that we are going to convert by subtracting 48 from the ASCII value of the char
			digit = (int)paymentChar[count] - 48;

			//handles conversion of values between 1000-9999
			if (paymentInt <= 9999 && paymentInt >= 1000) //deals with 4 digits
			{
				if (count != 2) //if count == 2, that means we are in the tens place
					findDigitName();
				else if (paymentChar[count] == '1')  //since we are now in the tens place, we are testing if the first value is '1'
				{
					testTens = true;  //if the value is 1, we assign the last two digits their name (11-19)
					findTensName();
					count = (int)strlen(paymentChar);  //sets count to the length of the C-String, ending the loop
				}
				else
					findTensName();
				

				
				if (paymentChar[count] != '0')
				{
					if (count == 0)
						convertedNumber.append(" thousand ");
					else if (count == 1)
						convertedNumber.append(" hundred ");
					else
						convertedNumber.append(" ");
				}
			}

			//handles conversion of values between 100-999
			else if (paymentInt <= 999 && paymentInt >= 100) //deals with numbers with 3 digits
			{
				if (count != 1) //deals with numbers not in the tens place
					findDigitName();
				else if (paymentChar[count] == '1') //likewise with the 1000s conversion, this will deal with digits 10-19
				{
					testTens = true;
					findTensName();
					count = (int)strlen(paymentChar);
				}
				else
					findTensName();
			

				if (paymentChar[count] != '0')
				{
					if (count == 0)
						convertedNumber.append(" hundred ");
					else
						convertedNumber.append(" ");
				}
			}

			//handles conversion of values between 20-99
			else if (paymentInt <= 99 && paymentInt >= 20) 
			{
				if (count != 0)
					findDigitName();
				else if (paymentChar[count] == '1')
				{
					testTens = true;
					findTensName();
					count = (int)strlen(paymentChar);
				}
				else
					findTensName();
				
				if (paymentChar[count] != '0')
						convertedNumber.append(" ");
			}
		}
	} //End of the conversion

}
//-------------------------------------------------------------------------------------------------------------------------------

//finds the digit's name based on the value of "digit"
void NumberConversion::findDigitName()
{
	if (digit >= 1 && digit <= 9)
		convertedNumber.append(ones[digit - 1]);
}
//-------------------------------------------------------------------------------------------------------------------------------

//find's the tens (10,20...) or teens(10-19) value by testing the value of "digit"
void NumberConversion::findTensName()
{
	if (testTens)
	{
		if (digit >= 0 && digit <= 9)
			convertedNumber.append(teens[digit]);
	}
	else
	{
		if (digit >= 2 && digit <= 9)
			convertedNumber.append(tens[digit - 2]);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------

std::string NumberConversion::getCentsValue(float payment)
{
	/*
		I came across several problems when trying to get decimal place value using a string. 
		I knew that finding the decimal value can actually be done with just one line of code:
		decimalVal = (number - (int)number) * 100;
		I was going to fall back on this if I couldn't get this function to work, but what I have right now works.
		Doing it this way, using string methods, was what the project challenge wanted us to do.
	*/

	int decimalLocation;
	std::ostringstream ostr;
	ostr << payment;
	std::string decimalPart = ostr.str();

	decimalLocation = decimalPart.find(".");

	if (decimalLocation != -1) //checks if a decimal spot was found in the string
	{
		//if the first digit in the decimal spot is a 0, this if-statement will set the string to the last value instead
		if (decimalPart[decimalLocation + 1] == '0')
		{
			decimalPart[0] = decimalPart[decimalLocation + 2];
			decimalPart[1] = '\0';
			decimalPart.erase(1, 8);
		}
		else
		{
			//since the first value wasn't a '0', we will assign the first digit place the first value found after the '.'
			decimalPart[0] = decimalPart[decimalLocation + 1];
			//this if-statement will test if the last number is a '0' or if it is the null terminator '\0', and will assign the next place value with '0'
			if (decimalPart[decimalLocation + 2] == '0' || decimalPart[decimalLocation + 2] == '\0')
			{
				decimalPart[1] = '0';
				decimalPart.erase(2, 7);
			}
			else
			{
				decimalPart[1] = decimalPart[decimalLocation + 2];
				decimalPart.erase(2, 7);
			}
		}
	}
	else
		decimalPart = "0";

	return decimalPart;
}
//-------------------------------------------------------------------------------------------------------------------------------