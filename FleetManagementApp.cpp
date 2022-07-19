// Fleet Management software

#include <iostream>
#include <string>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<sstream>
using namespace std;

void addtruck();
void equiptSelect();
void startup();
void menu();

int main() {

	menu();

	return 0;
}

void equiptSelect() {
	string unitNum1, input, line;
	string unitNum, makeModel, serialNum, plate;
	string a, b, c;
	char ans = 'y' || 'y';
	cout << "What unit number Are you Servicing?: "; cin >> unitNum1;
	ifstream file("trucks.txt");
	if (file.is_open())
	{
		file >> unitNum >> a >> makeModel >> b >> serialNum >> c >> plate;
		while (unitNum1 != unitNum)
		{
			file >> unitNum >> a >> makeModel >> b >> serialNum >> c >> plate;
		}
		cout << "The Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl;
		cout << "If this is correct please type Y and hit enter: "; cin >> ans;
		file.close();
		if (ans == 'y' || ans == 'Y')
		{
			string mechanic, date;
			double qty;
			int quickjob;
			string partNum, partDiscrpt, workdone, amtoil;
			cout << "Enter your name: "; cin >> mechanic;
			cout << "Enter the date: "; cin >> date;
			cout << mechanic << " is working on " << unitNum << " " << makeModel << " at date of " << date << endl;
			cout << "Quick Job choices number and repair" << "1) Oil Sample \n 2) Change Oil and Filters \n 3) Change Fuel Filters \n 4) Change Air Filters"
				<< "\n 5)Grease \n 6) Radiator \n 7) Transmission \n 8) Rears \n 9) Front Wheels \n 10) Tire Pressure \n 11) Lights \n 12) Brakes \n 13) Other \n";


			ofstream truckfile(unitNum + makeModel + ".txt", ios::app);
			if (file.is_open())
			{
				truckfile << mechanic << " is working on " << unitNum << " " << makeModel << " at date of " << date << endl;
				file.close();
			}
			else
			{
				cout << "File not found!";
			}

		}
		else
		{
			equiptSelect();
		}
	}
	else
	{
		cout << "File is not found!";
	}
}

void addtruck() {
	char ans = 'Y' && 'y';
	string unitNum, makeModel, serialNum, plate;
	cout << "Enter Unit Number: ";
	cin >> unitNum;
	cout << "Enter Make / Model: ";
	cin >> makeModel;
	cout << "Enter Serial Number: ";
	cin >> serialNum;
	cout << "Enter License Plate: ";
	cin >> plate;
	ofstream fout;
	ifstream fin;
	fin.open("trucks.txt");
	fout.open("trucks.txt", ios::app);
	if (!fin.is_open()) {

		cout << "File not found";
	}
	else {
		fout << endl << unitNum << " - " << makeModel << " - " << serialNum << " - " << plate;
		fin.close();
		fout.close();
	}
	cout << "Do you want to add a truck (No Spaces) (Y or y): "; cin >> ans;
	if (ans == 'Y' || ans == 'y') {
		addtruck();
	}
	else
	{
		exit(25);
	}

}

void startup() {
	int pin, checkpin;
	string name, a, checkname;
	cout << "Enter your Name: "; cin >> checkname;
	cout << "Enter your Pin: "; cin >> checkpin;
	ifstream fin;
	fin.open("username.txt");
	if (!fin.is_open()) {

		cout << "File not found";
	}
	else {
		fin >> name >> a >> pin;

		if (checkname == name && checkpin == pin) {
			fin.close();
			addtruck();
		}
		else
		{
			cout << "Your Information is wrong!" << endl;
			fin.close();
			startup();

		}
	}
}
void menu() {
	int choice;
	cout << "Choose what you would like to do: "; cin >> choice;
	switch (choice)
	{
	case 1:
		equiptSelect();
		break;
	case 2:
		menu();
		break;
	case 3:
		addtruck();
		break;
	default:
		cout << "Not a choice tru again!" << endl;
		menu();
	}
}