// Fleet Management software
// Version 1.11
//Last Updated 7/29/22
//Nicholas Hionas

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;
void addtruck();
void standardService();
void startup();
void menu();
void test(char& ans, string& makeModel, string& unitNum, string& serialNum, string& plate);
void serviceSwitch(string& makeModel, string& unitNum, string& mechanic, string& date, int& hrMi, string& x);
void repair();
void repairService(char& ans, string& makeModel, string& unitNum, string& serialNum, string& plate);
void ticket();
void createTicket();
void status();
void statusChange();

int main() {
	
	menu();

	return 0;
}

void statusChange()
{
	string makeModel, eqNum, date, issue, status;
	string a, b, c, d, e, f, g, h;
	char ans = 'y' || 'Y';
	int hours, serinterval, Wo = 0,pwo,choice;
	ifstream fileIn("tickets.txt");
	ofstream fileOut("tickets.txt", ios::app);
	cout << "Enter Work Order Number" << endl; cin >> pwo;
	do
	{
		fileIn >> a >> Wo >> b >> makeModel >> c >> eqNum >> d >> date >> e >> issue >> f >> hours >> g >> serinterval >> h >> status;
		if (pwo == Wo)
		{
			break;
		}
	} while (!fileIn.eof());
	cout << a << Wo << b << makeModel << c << eqNum << d << date << e << issue << f << hours << g << serinterval << h << status << endl;
	cout << "Is the the ticket you wanted?(Y for yes): "; cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		cout << "\nChange status 1) Done 2) Working on;"; cin >> choice;

		switch (choice)
		{
		case 1:
			status = "Done";
			cout << "Enter the date: "; cin >> date;
			fileOut << "\nTicket: " << Wo << " Machine: " << makeModel << " Equiptment#: " << eqNum << " Date: " << date << " Issue " << issue
				    << " Current_Hr/Miles: " << hours << " Next_Service: " << serinterval << " Status: " << status << endl;
			break;
		case 2:
			status = "WorkingOn";
			cout << "Enter the date: "; cin >> date;
			fileOut << "\nTicket: " << Wo << " Machine: " << makeModel << " Equiptment#: " << eqNum << " Date: " << date << " Issue " << issue
				    << " Current_Hr/Miles: " << hours << " Next_Service: " << serinterval << " Status: " << status << endl;
			break;
		default:
			cout << "Not a choice!";
			statusChange();
		}
		fileIn.close();
		fileOut.close();
	}
	ticket();
}

void status()
{
	string makeModel, eqNum, date, issue, status;
	string a, b, c, d, e, f, g, h;
	char ans = 'y' || 'Y';
	int hours, serinterval,Wo=0;
	ifstream fileIn("tickets.txt");
		while (!fileIn.eof())
		{
			fileIn >> a >> Wo >> b >> makeModel >> c >> eqNum >> d >> date >> e >> issue >> f >> hours >> g >> serinterval >> h >> status;
			cout << a << Wo << b << makeModel << c << eqNum << d << date << e << issue << f << hours << g << serinterval << h << status << endl;
		}
		cout << endl << endl;
	fileIn.close();
	ticket();
}

void createTicket() {
	string makeModel, eqNum, date, issue, status;
	string a, b, c, d, e, f, g, h;
	char ans = 'y' || 'Y';
	int hours, serinterval, Wo=0;
	ofstream fileOut("tickets.txt", ios::app);
	ifstream fin("tickets.txt", ios::app);
	cout << "Please enter equiptment maitnence or repair information " << "Order (MakeModel, Equiptment Number, Date, Issue, Hours, Next Service Date: )";
	cin >> makeModel >> eqNum >> date >> issue >> hours >> serinterval;
	
	if (issue == "none" || "None")
	{
		status = "NoProblems";
	}
	else if(issue == "needsService" || "needsservice" || "NeedsService")
	{
		status = "NeedsService";
	}
	else
	{
		status = "NeedsRepair";
	}
	while (!fin.eof())
	{
		fin >> a >> Wo >> b >> makeModel >> c >> eqNum >> d >> date >> e >> issue >> f >> hours >> g >> serinterval >> h >> status;
	}
	Wo++;
		cout << "Ticket: " << Wo << " Machine: " << makeModel << " Equiptment#: " << eqNum << " Date: " << date << " Issue " << issue
			 << " Current_Hr/Miles: " << hours << " Next_Service: " << serinterval << " Status: " << status << endl;
		cout << "Is this correct? (y for Yes)" << endl; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			fileOut << "\nTicket: " << Wo << " Machine: " << makeModel << " Equiptment#: " << eqNum << " Date: " << date << " Issue " << issue
				    << " Current_Hr/Miles: " << hours << " Next_Service: " << serinterval << " Status: " << status << endl;
			cout << "\nDo You want to add another machine? (Y for yes): "; cin >> ans;
			if (ans == 'y' || ans == 'Y')
			{
				createTicket();
			}
			else
			{
				fileOut.close();
				menu();
			}
		}
		else
		{
			createTicket();
		}
}

void ticket() {

	int choice;
	cout << " 1) Create Ticket \n 2) Status Check On Tickets \n 3) Change Status \n 4) Main Menu \n";
	cout << "Choose what you would like to do" << endl; cin >> choice;
	switch (choice)
	{
	case 1:
		createTicket();
		break;
	case 2:
		status();
		break;
	case 3:
		statusChange();
		break;
	case 4:
		menu();
		break;
	default:
		cout << "Not a choice!";
		ticket();
	}
}

void repairSwitch(string& makeModel, string& unitNum, string& mechanic, string& date, int& hrMi, string& x) {
	string partNum, partDiscrpt, work;
	int qty, quickjob;
	char ans = 'y' || 'Y';
	ofstream truckfile(unitNum + makeModel + ".txt", ios::app);
	truckfile << endl << endl << mechanic << " is working on " << unitNum << " " << makeModel << " at date of " << date << " With " << hrMi << " " << x << endl;
	cin >> quickjob;
	switch (quickjob)
	{
	case 1: //Engine
		cout << "Engine Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Engine Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 2: // Fuel System
		cout << "Fuel System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Fuel System Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 3://Ignition System
		cout << "Ignition System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Ignition System Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 4://Electrical System
		cout << "Electrical System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Electrical System Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 5://Exhaust System
		cout << "Exhaust System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Exhaust System Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 6:// Drive Train
		cout << "Drive Train Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Drive Train Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 7://Suspension and Steering System
		cout << "Suspension and Steering Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Suspension and Steering Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
	case 8://Brake Systems
		cout << "Brake System" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Brake System \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 9://Frame and Body Repair
		cout << "Frame and Body Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Frame and Body Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 10://Cooling System
		cout << "Cooling System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Cooling Systems Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 11://Tire Repair
		cout << "Tire Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Tire Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 12://Interior Repair
		cout << "Interior Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Interior Repair \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 13://Other
		cout << "Misc Repair See Notes" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Misc Repair See Notes \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	default:
		cout << "Not A Choice!" << endl;
		serviceSwitch(makeModel, unitNum, mechanic, date, hrMi, x);
	}

}

void repairService(char& ans, string& makeModel, string& unitNum, string& serialNum, string& plate) {
	string mechanic, date, qty, x;
	int hrMi;
	cout << "\nThe Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl << endl;
	cout << "If this is correct please type Y and hit enter: "; cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		cout << "\n\nEnter your name: "; cin >> mechanic;
		cout << "Enter the date: "; cin >> date;
		cout << "Enter Miles or Hours (EX 69000 Mi or 4500 Hr): "; cin >> hrMi >> x;
		cout << mechanic << " is working on " << unitNum << " " << makeModel << " at date of " << date << " with " << hrMi << " " << x << endl;
		cout << "\n 1) Engine \n 2) Fuel System \n 3) Ignition System \n 4) Electrical System"
			 << "\n 5) Exhaust System \n 6) Drive Train \n 7) Suspension and Steering System"
			 << "\n 8) Brake System \n 9) Frame and Body \n 10) Cooling System \n 11) Tire Repair \n 12) Interior Repair \n 13) Other \n";
		cout << "Choose a number for the repair you are doing: ";
	}
	else
	{
		menu();
	}
	repairSwitch(makeModel, unitNum, mechanic, date, hrMi, x);
}

void repair() {
	string unitNum, makeModel, serialNum, plate, unitNum1, input, line, a, b, c;
	char ans = 'y' || 'y';
	cout << "What unit number do you want to work on (EX LT-212)?: "; cin >> unitNum1;
	ifstream file("trucks.txt");
	if (file.is_open())
	{

		file >> unitNum >> a >> makeModel >> b >> serialNum >> c >> plate;
		if (unitNum1 == unitNum)
		{
			repairService(ans, makeModel, unitNum, serialNum, plate);
		}
		else
		{
			while (!file.eof() && unitNum1 != unitNum)
			{
				file >> unitNum >> a >> makeModel >> b >> serialNum >> c >> plate;

				if (file.eof() && unitNum1 != unitNum)
				{
					cout << "No machine is found!" << endl;
					menu();
				}
				else if (file.eof() && unitNum1 == unitNum)
				{
					cout << "\nThe Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl << endl;
					cout << "If this is correct please type Y and hit enter: "; cin >> ans;
					file.close();
					repairService(ans, makeModel, unitNum, serialNum, plate);
				}
				else if (!file.eof() && unitNum1 == unitNum)
				{
					cout << "\nThe Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl << endl;
					cout << "If this is correct please type Y and hit enter: "; cin >> ans;
					file.close();
					repairService(ans, makeModel, unitNum, serialNum, plate);
				}
			}
		}
	}
}

void standardService() {
	string unitNum, makeModel, serialNum, plate, unitNum1, input, line, a, b, c;
	char ans = 'y' || 'y';
	cout << "What unit number do you want to work on (EX LT-212)?: "; cin >> unitNum1;
	ifstream file("trucks.txt");
	if (file.is_open())
	{

		file >> unitNum >> a >> makeModel >> b >> serialNum >> c >> plate;
		if (unitNum1 == unitNum)
		{
			test(ans,makeModel,unitNum,serialNum,plate);
		}
		else 
		{
			while (!file.eof() && unitNum1 != unitNum)
			{
				file >> unitNum >> a >> makeModel >> b >> serialNum >> c >> plate;

				if (file.eof() && unitNum1 != unitNum)
				{
					cout << "No machine is found!" << endl;
					menu();
				}
				else if (file.eof() && unitNum1 == unitNum)
				{
					cout << "\nThe Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl << endl;
					cout << "If this is correct please type Y and hit enter: "; cin >> ans;
					file.close();
					test(ans, makeModel, unitNum, serialNum, plate);
				}
				else if (!file.eof() && unitNum1 == unitNum)
				{
					cout << "\nThe Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl << endl;
					cout << "If this is correct please type Y and hit enter: "; cin >> ans;
					file.close();
					test(ans, makeModel, unitNum, serialNum, plate);
				}
			}
		}

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
		ofstream other(unitNum + makeModel + ".txt");
		other.close();
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
	char ans = 'Y' && 'y';
	string unitNum, makeModel, serialNum, plate, unitNum1, input, line, a, b, c;
	cout << endl << endl;
	ifstream file("trucks.txt");
	while (!file.eof())
	{
		file >> unitNum >> a >> makeModel >> b >> serialNum >> c >> plate;
		cout << unitNum << " - " << makeModel << " - " << serialNum << " - " << plate << endl;
	}
	file.close();
	cout << "\n 1) Standard Service \n 2) Repairs \n 3) Add New Equiptment \n 4) Exit Program \n 5) Tickets \n";
	cout << "Choose what you would like to do: "; cin >> choice;
	switch (choice)
	{
	case 1:
		standardService();
		break;
	case 2:
		repair();
		break;
	case 3:
		addtruck();
		break;
	case 4:
		exit(1);
		break;
	case 5:
		ticket();
		break;
	default:
		cout << "Not a choice try again!" << endl;
		menu();
	}
}

void test(char& ans, string& makeModel, string& unitNum, string& serialNum, string& plate) {
	string mechanic, date, qty, x;
	int hrMi;
	cout << "\nThe Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl << endl;
	cout << "If this is correct please type Y and hit enter: "; cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		cout << "\n\nEnter your name: "; cin >> mechanic;
		cout << "Enter the date: "; cin >> date;
		cout << "Enter Miles or Hours (EX 69000 Mi or 4500 Hr): "; cin >> hrMi >> x;
		cout << mechanic << " is working on " << unitNum << " " << makeModel << " at date of " << date << " with " << hrMi << " " << x << endl;
		cout << "\n 1) Oil Sample \n 2) Change Oil and Filters \n 3) Change Fuel Filters \n 4) Change Air Filters"
			 << "\n 5) Grease \n 6) Radiator \n 7) Transmission \n 8) Rears \n 9) Front Wheels \n 10) Tire Pressure \n 11) Lights \n 12) Brakes \n 13) Other \n";
		cout << "Choose a Number for the service you are doing: ";
	}
	else
	{
		menu();
	}
	serviceSwitch(makeModel,unitNum,mechanic,date,hrMi,x);

}

void serviceSwitch(string& makeModel, string& unitNum,string& mechanic,string& date, int& hrMi, string& x) {
	string partNum, partDiscrpt, work;
	int qty, quickjob;
	char ans = 'y' || 'Y';
	ofstream truckfile(unitNum + makeModel + ".txt", ios::app);
	truckfile << endl << endl << mechanic << " is working on " << unitNum << " " << makeModel << " at date of " << date << " With " << hrMi << " " << x << endl;
	cin >> quickjob;
	switch (quickjob)
	{
	case 1: //Oil Sample
		cout << "Send Out Oil Sample" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Sent Out Oil Sample \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 2: // Change Oil and Filters
		cout << "Changed Oil and Filters" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Changed Oil and Filters \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 3://Change Fuel Filters
		cout << "Changed Fuel Filters" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Changed Fuel Filters \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 4://Change Air Filters
		cout << "Changed Air Filters" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Changed Air Filters \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
			{
				do
				{
					truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
					cin >> qty >> partNum >> partDiscrpt >> work;
					truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
					cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
				} while (ans == 'y' || ans == 'Y');
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				truckfile.close();
				menu();
			}
			else
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				truckfile.close();
				menu();
			}
		break;
	case 5://Grease
		cout << "Greased Machine" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Greased Machine \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 6:// Radiator
		cout << "Radiator Service" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Radiator Service \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 7://Transmission
		cout << "Transmission Service" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Transmission Service \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
	case 8://Rears
		cout << "Rears Service" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Rears Service \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 9://Front Wheels
		cout << "Front Wheels Service" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Front Wheels Service \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 10://Tire Pressure
		cout << "Tire Pressure Ajustments" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Tire Pressure Adjustments \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 11://:Lights
		cout << "Lights Service" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Lights Service \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 12://Brakes
		cout << "Brakes Service" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Brakes Service \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	case 13://Other
		cout << "Misc Service See Notes" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Misc Service See Notes \n";
		cin >> qty >> partNum >> partDiscrpt >> work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
				cin >> qty >> partNum >> partDiscrpt >> work;
				truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << qty << "\nParts Number = " << partNum << "\nParts Description = " << partDiscrpt << "\nWork Description = " << work;
			truckfile.close();
			menu();
		}
		break;
	default:
		cout << "Not A Choice!" << endl;
		serviceSwitch( makeModel,  unitNum,  mechanic,  date,hrMi,x);
	}
}