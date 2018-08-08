/*****************************************************************************************
Project Name: Lab 1
Name: Kristopher Lowell
Date Completed: 8/7/2018
Purpose: To accept names of items, their prices, and a credit card number and then print 
the items, prices, sub-total, taxes, total, and last four of the credit card number
*****************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

const double TAX_RATE = 0.10;

double calculate_total(vector <double> prices, unsigned numOfItems, double *subTotal, double *taxes);
double round_total(double total);
void print_credit_card_number(long long unsigned ccNumber);

int main()
{
	unsigned billNumber = 0;

	time_t t;
	tm *now;
	unsigned month, day, year;

	vector <string> items;			// Using vectors for dynamic allocation purposes
	vector <double> prices;

	string strEntry;				// Input "buffers" for said vectors
	double dblEntry;

	double subTotal, taxes, total;

	long long unsigned ccNumber = 0;

	unsigned numOfItems;

	char another;

	do
	{
		t = time(0);					// Getting the local time and setting date accordingly
		now = localtime(&t);
		month = now->tm_mon + 1;
		day = now->tm_mday;
		year = now->tm_year + 1900;

		ccNumber = 0;					// Resetting credit card number and number of items for new bill
		numOfItems = 0;

		cout << "Processing Bill #" << ++billNumber << ":" << endl;

		do								// Accepting input for items and their prices
		{							
			cout << endl << "Enter the name of item #" << numOfItems + 1 << ": ";
			cin >> strEntry;
			
			if (strEntry.front() != '-')	// Enter "-" to end input for items
			{
				items.push_back(strEntry);

				cout << "Enter the price of " << strEntry << ": ";
				cin >> dblEntry;

				prices.push_back(dblEntry);

				numOfItems++;
			}

		} while (strEntry.front() != '-');

		total = calculate_total(prices, numOfItems, &subTotal, &taxes);
		total = round_total(total);

		while (ccNumber <= 999999999999999 || ccNumber > 9999999999999999)	// Rudimentary check for a 16-digit entry
		{
			cout << endl << "Enter the 16-digit credit card number: ";
			cin >> ccNumber;
		}

		cout << endl << "Printing Bill #" << billNumber << ":" << endl << endl;		// Starting the printing sequence

		cout << "Bill Number: " << billNumber << endl;
		cout << "Bill Date: " << month << "/" << day << "/" << year << endl;

		cout.setf(ios_base::fixed);
		cout.precision(2);

		for (unsigned i = 0; i < numOfItems; i++)					// Printing all the item names with their prices
			cout << items[i] << "\t\t $ " << prices[i] << endl;

		cout << "Sub-Total: \t $ " << subTotal << endl;				// Printing sub-total

		cout.precision(0);
		cout << "Tax (@" << TAX_RATE * 100 << "%): \t $ ";			// Printing tax percentage
		cout.precision(2);
		cout << taxes << endl;										// Printing amount of taxes for bill

		cout << "Total: \t\t $ " << total << endl;

		cout << "Cash: No" << endl;
		cout << "Debit Card: No" << endl;

		print_credit_card_number(ccNumber);
		cout << endl;

		items.clear();				// Empty the vectors for a new bill
		prices.clear();

		another = ' ';

		while (another != 'Y' && another != 'y' && another != 'N' && another != 'n')
		{
			cout << "Process and print another bill? (Y/N): ";		// Asking user if a new bill is to be created
			cin >> another;
		}

		cout << endl;

	}while (another == 'Y' || another == 'y');

}

double calculate_total(vector<double> prices, unsigned numOfItems, double *subTotal, double *taxes)
{
	*subTotal = 0;		// Ensures sub-total doesn't have any carry-over from previous bills
	
	for (unsigned i = 0; i < numOfItems; i++)
		*subTotal += prices[i];		// Calculating sub-total by adding all item prices

	*taxes = *subTotal * TAX_RATE;	// Calculating taxes for bill

	return *subTotal + *taxes;		// Returns the total by adding the subtotal and taxes
}

double round_total(double total)
{
	int dollar;

	total += 0.50;
	dollar = (int) total;			// Adds 0.50 and truncates to round to nearest dollar

	return (double) dollar;
}

void print_credit_card_number(long long unsigned ccNumber)
{
	unsigned displayNumber = ccNumber % 10000;		// Getting the last 4 digits from credit card number

	cout << "Credit Card Number: XXXXXXXXXXXX" << displayNumber << endl;
}