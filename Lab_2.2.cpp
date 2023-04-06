#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

int width = 40, numWidth = 10;
using namespace std;

map<string, int> GetData(string finName, string foutName)
{
	ifstream fin;
	fin.open(finName);

	fin.ignore(15, '\0');
	string customer;
	getline(fin, customer, '\n');

	fin.ignore(15, '\0');
	string account;
	getline(fin, account, '\n');

	fin.ignore(15, '\0');
	string date;
	getline(fin, date, '\n');

	ofstream fout;
	fout.open(foutName);

	fout << "Programmer: Me\n\n";
	fout << "Customer:" << setiosflags(ios::right) << setw(width - 9) << customer << endl;
	fout << "Account:" << setiosflags(ios::right) << setw(width - 8) << account << endl;
	fout << "Billing date:" << setiosflags(ios::right) << setw(width - 13) << date << endl << endl;

	fout.close();

	for (int i = 0; i < 3; i++)
	{
		fin.ignore(255, '\n');
	}

	map<string, int> data;
	while (!fin.eof())
	{
		string key;
		int value;
		fin >> key;
		fin.ignore(14, '\0');
		fin >> value;
		data[key] += value;
	}
	fin.close();
	return data;
}

string PutTime(int time)
{
	int hours, minutes;
	string sHours, sMinutes;
	hours = time / 60;
	minutes = time % 60;
	if (hours < 10)
		sHours = "0" + to_string(hours);
	else
		sHours = to_string(hours);
	if (minutes < 10)
		sMinutes = "0" + to_string(minutes);
	else
		sMinutes = to_string(minutes);
	return sHours + ":" + sMinutes;
}

void CreateOutput(string foutName, map<string, int> data)
{
	ofstream fout;
	fout.open(foutName, ios::app);

	int peakSum = data["P"], cardSum = data["C"], offPeakSum = data["O"];
	fout << setiosflags(ios::right) << setw(width-10) << "Minutes" << setiosflags(ios::right) << setw(10) << "Charge" << endl;

	fout << setw(width) << setfill('=') << "" << endl;
	float peakCharge = 0, offPeakCharge = 0, cardCharge = 0;
	if (offPeakSum > 100)
		offPeakCharge = 100 * 0.05 + (offPeakSum - 100) * 0.03;
	else
		offPeakCharge = offPeakSum * 0.05;
	peakCharge = peakSum * 0.10;
	cardCharge = cardSum * 0.25;
	float planFee = 4.95, cardFee = 1.00, universalCharge = 5.31, localTax = 1.25, stateTax , total;

	stateTax = floor((cardFee + peakCharge + offPeakCharge + cardCharge + planFee) * 0.4) / 100;

	fout << "Peak:" << setiosflags(ios::right) << setw(width - 5 - numWidth) << setfill(' ') << PutTime(peakSum)
		<< setiosflags(ios::right) << setw(numWidth) << setprecision(2) << fixed << peakCharge << endl;

	fout << "Offpeak:" << setiosflags(ios::right) << setw(width - 8 - numWidth) << PutTime(offPeakSum)
		<< setiosflags(ios::right) << setw(numWidth) << setprecision(2) << fixed << offPeakCharge << endl;

	fout << "Card:" << setiosflags(ios::right) << setw(width - 5 - numWidth) << PutTime(cardSum)
		<< setiosflags(ios::right) << setw(numWidth) << setprecision(2) << fixed << cardCharge << endl;

	fout << setw(width) << setfill('=') << "" << endl;

	fout << "Subtotal:" << setiosflags(ios::right) << setw(width - 9) << setfill(' ')
		<< setprecision(2) << fixed << peakCharge + cardCharge + offPeakCharge << endl;

	fout << "Calling plan fee:" << setiosflags(ios::right) << setw(width - 17)
		<< setprecision(2) << fixed <<  planFee << endl;

	fout << "Calling card fee:" << setiosflags(ios::right) << setw(width - 17)
		<< setprecision(2) << fixed << cardFee << endl;

	fout << "Universal connectivity charge:" << setiosflags(ios::right) << setw(width - 30)
		<< setprecision(2) << fixed << universalCharge << endl;

	fout << "Local tax:" << setiosflags(ios::right) << setw(width - 10)
		<< setprecision(2) << fixed << localTax << endl;

	fout << "State tax:" << setiosflags(ios::right) << setw(width - 10)
		<< setprecision(2) << fixed << stateTax << endl;

	fout << setw(width) << setfill('=') << "" << endl;

	total = cardFee + peakCharge + offPeakCharge + cardCharge + planFee + universalCharge + localTax + stateTax;
	fout << "Total:" << setiosflags(ios::right) << setw(width - 6) << setfill(' ')
		<< setprecision(2) << fixed << total << endl;

	fout.close();
}



int main()
{
	string finName = "2.CallDetails.txt";
	string foutName = "Out.txt";
	map<string, int> data = GetData(finName, foutName);
	CreateOutput(foutName, data);
}
