/*
--Problem Statement--
Check Writer
Write a program that displays a simulated paycheck. The program should ask the user to enter
the date, payee's name, and the amount of the check. It should then display a simulated check
with the dollar amount spelled out, as shown here:

Date 12/24/2012


Pay to the Order of: John Phillips			$1920.85
One thousand nine hundred twenty and 85 cents

You may assume the amount is no greater than $10000. Be sure to format the numeric value of
the check in fixed-point notation with two decimal placees of precision. Be sure the decimal
place always displays, even when the number is zero or has no fractional part. Use either
C-strings or string class objects in this program.
--End--

This program is a check writing simulation. The user will enter their name, a date (was unsure
if the date was suppose to be current, so I just set the minimum year to be 1950 and the max to
be 2016) and the check amount. The check amount can't be less than 0.1 or greater than 10,000.00.

I am a little annoyed with how it turn out. The conversion (located in NumberConversion.cpp) method was
sloppy, and can't really be applied to much bigger numbers without typing out way more code. Perhaps
I could have used the length() function to determine whether the number was in the thousands or ten thousands.

Written by Billy Matthews, Feb. 2016
*/

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "NumberConversion.h"

void splashScreen();
void clearScreen();
bool validateDate(int, int, int);

//-------------------------------------------------------------------------------------------------------------------------------
int main()
{
	//declaration and initilization of variables
	int paymentInteger, month, day, year;
	char repeatProcess = 'N', payment[9];
	std::string userName, userInput, convertedPayment, decimalSpot;
	float paymentAmount = 0.0;

	NumberConversion convertedNumber;

	splashScreen();
	do
	{
		clearScreen();

		//if the program is running a second time, then this statement will empty the string
		if (repeatProcess == 'Y')
			convertedPayment.clear();

		std::cout << "Enter the payee's name: ";
		std::getline(std::cin, userName);
		while (userName[0] == NULL)
		{
			std::cout << "\nThere must be a name, so please re-enter the payee's name: ";
			std::getline(std::cin, userName);
		}
		std::cin.clear();

		//finds the date
		std::cout << "\nEnter the date of the check. Use numeric values.\n";

		//gets the year
		while (true)
		{
			std::cout << "Year: ";
			std::getline(std::cin, userInput);

			std::stringstream myStream(userInput);
			if (myStream >> year && year >= 1950 && year <= 2016)
				break;
			std::cout << "\nInvalid year! Make sure the year chosen is a valid year.\nChecks written before 1950 can't be processed.\n";
		}

		//gets the month
		while (true)
		{
			std::cout << "Month: ";
			std::getline(std::cin, userInput);

			std::stringstream myStream(userInput);
			if (myStream >> month && month >= 1 && month <= 12)
				break;
			std::cout << "\nInvalid month! Make sure the month is between 1 through 12.\n";
		}

		//gets the day of the month
		while (true)
		{
			std::cout << "Day: ";
			std::getline(std::cin, userInput);

			std::stringstream myStream(userInput);
			if (myStream >> day && validateDate(year, month, day))
				break;
			std::cout << "\nInvalid Day! Make sure your day is a valid day for the month you've chosen.\n";
		}
			
		std::cin.clear();

		//gets the check's payment amoutn
		while (true)
		{
			std::cout << "\nEnter the payment amount: ";
			std::getline(std::cin, userInput);

			std::stringstream myStream(userInput);
			//validates that the user entered a number between 1 through 10000
			if (myStream >> paymentAmount && paymentAmount >= 0.0 && paymentAmount <= 10000.0)
				break;
			std::cout << "\nInvalid payment amount!\nPlease no special characters. Amount may not exceed $10,000.\n";
		}
		
		decimalSpot.clear();
		decimalSpot = convertedNumber.getCentsValue(paymentAmount);  //finds the decimal place and returns the value back to main

		//converts the payment amount into an integer, which will be used as for the conversion into words
		paymentInteger = static_cast<int>(paymentAmount);

		_itoa(paymentInteger, payment, 10);  //compiler error when just using "itoa"?

		//sends the C-string and integer version of the payment to the NumberConversion class
		convertedNumber.convertNumber(payment, paymentInteger);

		//gets the converted payment from the class
		convertedPayment = convertedNumber.getConvertedNumber();

		clearScreen();
		std::cout << "--------------------------- CHECK ---------------------------\n";
		std::cout << std::right << std::setw(44) << "Date: " << month << "/" << day << "/" << year;
		std::cout << "\n\n\nPay to the Order of: " << std::left << std::setw(18) << userName;
		std::cout << std::left << std::fixed << std::setprecision(2) << "      $" << paymentAmount << std::endl;
		std::cout << convertedPayment << "dollars and " << decimalSpot << " cents." << std::endl << std::endl;
		std::cout << "-------------------------------------------------------------\n\n";

		while (true)
		{
			std::cout << "Would you like to write another check? (Y/N)  ";
			std::getline(std::cin, userInput);

			if (userInput.length() == 1)
			{
				repeatProcess = userInput[0];
				repeatProcess = toupper(repeatProcess);
				if (repeatProcess == 'Y' || repeatProcess == 'N')
					break;
			}
			clearScreen();
			std::cout << "\nInvalid entry, please try again." << std::endl;
		}

	} while (repeatProcess == 'Y');

	std::cout << "\nThanks for using the program!\n\nPress Enter to exit. . .";
	std::cin.get();
	return 0;
}


//-------------------------------------------------------------------------------------------------------------------------------
void splashScreen()
{
	//greets the user to the program and explains the program's purpose
	std::string temp;
	std::cout << "Welcome to the Check Writer program!\nThis program will simulate a check with a dollar amount spelled out\nand "
		<< "will display your name along with the date.\nChecks above $10,000.00 can't be processed.\nMade by Billy Matthews, Feb. 2016.\n\nPress Enter to continue. . .";
	std::getline(std::cin, temp);
}

//-------------------------------------------------------------------------------------------------------------------------------
void clearScreen()
{
	//clears the screen
	std::cout << std::string(100, '\n');
}

/*-------------------------------------------------------------------------------------------------------------------------------
This function gets the date entered by the user and validates it. 
Mainly checking if the day the user has chosen is an actual day of the month they have chosen.
Getting the entire date in one input is what I wanted to do, but I opted for this method.
*/
bool validateDate(int yearChosen, int monthChosen, int dayChosen)
{
	bool goodDate = false;
	
	switch (monthChosen)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (dayChosen >= 1 && dayChosen <= 31)
			goodDate = true;
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		if (dayChosen >= 1 && dayChosen <= 30)
			goodDate = true;
		break;

	//since this last case is February, we will find out
	//whether or not the year is a leap year or not
	case 2: 
		if ((yearChosen % 4 == 0 && yearChosen % 100 != 0) || (yearChosen % 400 == 0))
		{
			if (dayChosen >= 1 && dayChosen <= 29)
				goodDate = true;
		}
		else if (dayChosen >= 1 && dayChosen <= 28)
			goodDate = true;
		break;

	default:
		goodDate = false;
		break;
	}
	return goodDate;
}
//-------------------------------------------------------------------------------------------------------------------------------