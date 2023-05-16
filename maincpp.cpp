// Fleet Management software
// Version 1.12
//Last Updated 1/17/2023
//Goal For Today: Fix Many Bugs in ticketing system as well as see if we can scew passwords and delete info once entered
//Nicholas Hionas

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdlib.h>

using namespace std;

void addtruck();
void standardService();
void startup();
void menu();
void test(char& ans, string& makeModel, string& unitNum, string& serialNum, string& plate);
void serviceSwitch(string& makeModel, string& unitNum, string& mechanic, string& date, int& hrMi, string& x);
void repairChoice();
void repairService(char& ans, string& makeModel, string& unitNum, string& serialNum, string& plate);
void ticket();
void createTicket();
void status();
void statusChange();
void checkSum(string& un, string& pw);
void createUser(string& un, string& pw);
void loginSwitch();
void adminLogin(string& un, string& pw);

class Users {
public:
	string username;
	string password;
	string Fname;
	string Lname;
	int birthdate;
};

class admins {
public:
	string amdminUsername = "Admin";
	string passwordUsername = "Administration0001";
};

class equiptment {
	public:
	string makeModel;
	string unitNum;
	string serialNum;
	string plate;
	string mechanic;
	string date;
	string partNum;
	string partDiscrpt;
	string work;
	int hrMi;
	int qty;
};

int main() {
	loginSwitch();
	return 0;
}

void checkSum(string& un, string& pw) {
	string un1, pw1, a;
	ifstream fin("U" + un + ".txt");
	if (fin.is_open())
	{
		fin >> un1 >> pw1;
		if (un1 == un && pw1 == pw)
		{
			system("cls");
			menu();
		}
		else
		{
			cout << "Username Or Password Is Inccorrect \n\n";
			loginSwitch();
		}
	}
	else
	{
		cout << "error code 0003";
	}

}

void createUser(string& un, string& pw) {
	Users access;
	string checkname, have;
	string un1, pw1, a;
	ifstream fin("admin.txt");
	if (fin.is_open())
	{
		fin >> un1 >> pw1;
		if (un1 == un && pw1 == pw)
		{
			ifstream userfile("user.txt");
			cout << "Hello please select a username: " << endl; cin >> access.username;
			if (!userfile.is_open())
			{
				cout << "File not found critical error";
				exit(0003);
			}
			else
			{
				while (!userfile.eof())
				{
					userfile >> checkname;
					if (access.username == checkname)
					{
						have = checkname;
					}
				}
				if (have == access.username)
				{
					cout << "Username is taken! try again" << endl;
					createUser(un, pw);
				}
				else
				{
					cout << "Congradulations " << access.username << " is not taken!" << endl;
				}
			}
			cout << "\nHello User " << access.username << " lets get you started! Follow the prompts: \n";
			cout << "Enter your First name: "; cin >> access.Fname;
			cout << "Enter your Last name: "; cin >> access.Lname;
			cout << "Enter your Birthdate (MMDDYYYY): "; cin >> access.birthdate;
			cout << "Enter your Password: "; cin >> access.password;
			cout << "Reenter your password: "; cin >> pw1;
			do {
				if (pw1 != access.password)
				{
					cout << "Enter your Password: "; cin >> access.password;
					cout << "Renter your password: "; cin >> pw1;
				}
			} while (pw1 != access.password);
			cout << "Username: " << access.username << endl;
			cout << "Password: " << access.password << endl;
			cout << "First Name: " << access.Fname << endl;
			cout << "Last Name: " << access.Lname << endl;
			cout << "Birthdate: " << access.birthdate << endl;
			char choice;
			cout << "Is this Information Correct? Enter y for yes \n"; cin >> choice;
			if (choice == 'y' || choice == 'Y')
			{
				ofstream fileout("user.txt", ios::app);
				fileout << "\n" << access.username;
				fileout.close();
				ofstream fout("U" + access.username + ".txt");
				fout << access.username << "\n" << access.password << "\n" << access.Fname << "\n" << access.Lname << "\n" << access.birthdate;
				fout.close();
				ifstream fin("U" + access.username + ".txt");
				fin >> access.username >> access.password >> access.Fname >> access.Lname >> access.birthdate;
				fin.close();
				loginSwitch();
			}
			else
				createUser(un, pw);
		}
		else
		{
			cout << "Username Or Password Is Inccorrect \n\n";
			system("cls");
			loginSwitch();
			
		}
	}
	else
	{
		cout << "error code 0003";
	}
	
}

void loginSwitch() {
	string un, pw;
	int choice;
	cout << "Hello please select what you would like to do.";
	cout << "\n1) Login \n2) Create User\n" << "3) Administration Login\n" << "4) Exit Program\n"; cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Please Enter Username: "; cin >> un;
		cout << "Please Enter Password: "; cin >> pw;
		checkSum(un, pw);
		break;
	case 2:
		cout << "Please Enter Administration Username: "; cin >> un;
		cout << "Please Enter Administration Password: "; cin >> pw;
		createUser(un, pw);
		break;
	case 3:
		cout << "Please Enter Administration Username: "; cin >> un;
		cout << "Please Enter Administration Password: "; cin >> pw;
		adminLogin(un, pw);
	case 4:
		exit(4);
		break;
	default:
		main();
	}
}

void adminLogin(string& un, string& pw) {
	string un1, pw1, a;
	ifstream fin("admin.txt");
	if (fin.is_open())
	{
		fin >> un1 >> pw1;
		if (un1 == un && pw1 == pw)
		{
			system("cls");
			menu();
		}
		else
		{
			cout << "Username Or Password Is Inccorrect \n\n";
			loginSwitch();
		}
	}
	else
	{
		cout << "error code 0003";
	}
}

void statusChange()
{
	string makeModel, eqNum, date, issue, status;
	string a, b, c, d, e, f, g, h;
	char ans = 'y' || 'Y';
	int hours, serinterval, Wo = 0, pwo, choice;
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
		cout << "\nChange status \n1) Done \n2) Working On \n3) Waiting On Parts"; cin >> choice;

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
		case 3:
			status = "WaitingOnParts";
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
	int hours, serinterval, Wo = 0;
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
	string makeModel, eqNum, date, issue, issue1, status, status1;
	string a, b, c, d, e, f, g, h;
	char ans = 'y' || 'Y';
	int hours, serinterval, Wo = 0;
	ofstream fileOut("tickets.txt", ios::app);
	ifstream fin("tickets.txt", ios::app);
	cout << "Please enter equiptment maitnence or repair information " << "Order (MakeModel, Equiptment Number, Date, Issue, Hours, Next Service Date: )";
	cin >> makeModel >> eqNum >> date >> issue1 >> hours >> serinterval;

	if (issue1 == "none" || issue1 == "None")
	{
		status1 = "NoProblems";
	}
	else if (issue1 == "needsService" || issue1 == "needsservice" || issue1 == "NeedsService")
	{
		status1 = "NeedsService";
	}
	else
	{
		status1 = "NeedsRepair";
	}
	while (!fin.eof())
	{
		fin >> a >> Wo >> b >> makeModel >> c >> eqNum >> d >> date >> e >> issue >> f >> hours >> g >> serinterval >> h >> status;
	}
	Wo++;
	cout << "Ticket: " << Wo << " Machine: " << makeModel << " Equiptment#: " << eqNum << " Date: " << date << " Issue " << issue1
		<< " Current_Hr/Miles: " << hours << " Next_Service: " << serinterval << " Status: " << status1 << endl;
	cout << "Is this correct? (y for Yes)" << endl; cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		fileOut << "\nTicket: " << Wo << " Machine: " << makeModel << " Equiptment#: " << eqNum << " Date: " << date << " Issue " << issue1
			<< " Current_Hr/Miles: " << hours << " Next_Service: " << serinterval << " Status: " << status1 << endl;
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
	equiptment access;
	int quickjob;
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
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 2: // Fuel System
		cout << "Fuel System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Fuel System Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 3://Ignition System
		cout << "Ignition System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Ignition System Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 4://Electrical System
		cout << "Electrical System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Electrical System Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 5://Exhaust System
		cout << "Exhaust System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Exhaust System Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 6:// Drive Train
		cout << "Drive Train Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Drive Train Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 7://Suspension and Steering System
		cout << "Suspension and Steering Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Suspension and Steering Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
	case 8://Brake Systems
		cout << "Brake System" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Brake System \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 9://Frame and Body Repair
		cout << "Frame and Body Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Frame and Body Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " <<  access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 10://Cooling System
		cout << "Cooling System Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Cooling Systems Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 11://Tire Repair
		cout << "Tire Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Tire Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 12://Interior Repair
		cout << "Interior Repair" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Interior Repair \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		break;
	case 13://Other
		cout << "Misc Repair See Notes" << endl;
		cout << "*****Notes NO SPACES**** \n 1) Quanity \n 2) Part Number \n 3) Part Name \n 4) work" << endl << endl;
		truckfile << "Service Number: " << quickjob << "\t\t\t\t\t Work Done: Misc Repair See Notes \n";
		cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
		cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			do
			{
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
				cin >> access.qty >> access.partNum >> access.partDiscrpt >> access.work;
				truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work << endl;
				cout << "Do you need to add another Part? (Y for Yes): "; cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
			truckfile.close();
			menu();
		}
		else
		{
			truckfile << endl << "Quanity = " << access.qty << "\nParts Number = " << access.partNum << "\nParts Description = " << access.partDiscrpt << "\nWork Description = " << access.work;
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
	equiptment access;
	string x;
	cout << "\nThe Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl << endl;
	cout << "If this is correct please type Y and hit enter: "; cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		cout << "\n\nEnter your name: "; cin >> access.mechanic;
		cout << "Enter the date: "; cin >> access.date;
		cout << "Enter Miles or Hours (EX 69000 Mi or 4500 Hr): "; cin >> access.hrMi >> x;
		cout << access.mechanic << " is working on " << unitNum << " " << makeModel << " at date of " << access.date << " with " << access.hrMi << " " << x << endl;
		cout << "\n 1) Engine \n 2) Fuel System \n 3) Ignition System \n 4) Electrical System"
			<< "\n 5) Exhaust System \n 6) Drive Train \n 7) Suspension and Steering System"
			<< "\n 8) Brake System \n 9) Frame and Body \n 10) Cooling System \n 11) Tire Repair \n 12) Interior Repair \n 13) Other \n";
		cout << "Choose a number for the repair you are doing: ";
	}
	else
	{
		menu();
	}
	repairSwitch(makeModel, unitNum, access.mechanic, access.date, access.hrMi, x);
}

void repairChoice() {
	equiptment access;
	string unitNum1, input, line, a, b, c;
	char ans = 'y' || 'y';
	cout << "What unit number do you want to work on (EX LT-212)?: "; cin >> unitNum1;
	ifstream file("trucks.txt");
	if (file.is_open())
	{

		file >> access.unitNum >> a >> access.makeModel >> b >> access.serialNum >> c >> access.plate;
		if (unitNum1 == access.unitNum)
		{
			repairService(ans, access.makeModel, access.unitNum, access.serialNum, access.plate);
		}
		else
		{
			while (!file.eof() && unitNum1 != access.unitNum)
			{
				file >> access.unitNum >> a >> access.makeModel >> b >> access.serialNum >> c >> access.plate;

				if (file.eof() && unitNum1 != access.unitNum)
				{
					cout << "No machine is found!" << endl;
					menu();
				}
				else if (file.eof() && unitNum1 == access.unitNum)
				{
					cout << "\nThe Unit you are servicing is: " << access.unitNum << " " << access.makeModel << " " << access.serialNum << " " << access.plate << endl << endl;
					cout << "If this is correct please type Y and hit enter: "; cin >> ans;
					file.close();
					repairService(ans, access.makeModel, access.unitNum, access.serialNum, access.plate);
				}
				else if (!file.eof() && unitNum1 == access.unitNum)
				{
					cout << "\nThe Unit you are servicing is: " << access.unitNum << " " << access.makeModel << " " << access.serialNum << " " << access.plate << endl << endl;
					cout << "If this is correct please type Y and hit enter: "; cin >> ans;
					file.close();
					repairService(ans, access.makeModel, access.unitNum, access.serialNum, access.plate);
				}
			}
		}
	}
}

void standardService() {
	equiptment access;
	string unitNum1, input, line, a, b, c;
	char ans = 'y' || 'y';
	cout << "What unit number do you want to work on (EX LT-212)?: "; cin >> unitNum1;
	ifstream file("trucks.txt");
	if (file.is_open())
	{

		file >> access.unitNum >> a >> access.makeModel >> b >> access.serialNum >> c >> access.plate;
		if (unitNum1 == access.unitNum)
		{
			test(ans, access.makeModel, access.unitNum, access.serialNum, access.plate);
		}
		else
		{
			while (!file.eof() && unitNum1 != access.unitNum)
			{
				file >> access.unitNum >> a >> access.makeModel >> b >> access.serialNum >> c >> access.plate;

				if (file.eof() && unitNum1 != access.unitNum)
				{
					cout << "No machine is found!" << endl;
					menu();
				}
				else if (file.eof() && unitNum1 == access.unitNum)
				{
					cout << "\nThe Unit you are servicing is: " << access.unitNum << " " << access.makeModel << " " << access.serialNum << " " << access.plate << endl << endl;
					cout << "If this is correct please type Y and hit enter: "; cin >> ans;
					file.close();
					test(ans, access.makeModel, access.unitNum, access.serialNum, access.plate);
				}
				else if (!file.eof() && unitNum1 == access.unitNum)
				{
					cout << "\nThe Unit you are servicing is: " << access.unitNum << " " << access.makeModel << " " << access.serialNum << " " << access.plate << endl << endl;
					cout << "If this is correct please type Y and hit enter: "; cin >> ans;
					file.close();
					test(ans, access.makeModel, access.unitNum, access.serialNum, access.plate);
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
	equiptment access;
	string a, b, c;
	cout << endl << endl;
	ifstream file("trucks.txt");
	while (!file.eof())
	{
		file >> access.unitNum >> a >> access.makeModel >> b >> access.serialNum >> c >> access.plate;
		cout << access.unitNum << " - " << access.makeModel << " - " << access.serialNum << " - " << access.plate << endl;
	}
	file.close();
	cout << "\n 1) Standard Service \n 2) Repairs \n 3) Add New Equiptment \n 4) Tickets \n 5) Exit Program \n";
	cout << "Choose what you would like to do: "; cin >> choice;
	switch (choice)
	{
	case 1:
		standardService();
		break;
	case 2:
		repairChoice();
		break;
	case 3:
		addtruck();
		break;
	case 4:
		ticket();
		break;
	case 5:
		exit(01);
		break;
	default:
		cout << "Not a choice try again!" << endl;
		menu();
	}
}

void test(char& ans, string& makeModel, string& unitNum, string& serialNum, string& plate) {
	equiptment access;
	string qty, x;
	cout << "\nThe Unit you are servicing is: " << unitNum << " " << makeModel << " " << serialNum << " " << plate << endl << endl;
	cout << "If this is correct please type Y and hit enter: "; cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		cout << "\n\nEnter your name: "; cin >> access.mechanic;
		cout << "Enter the date: "; cin >> access.date;
		cout << "Enter Miles or Hours (EX 69000 Mi or 4500 Hr): "; cin >> access.hrMi >> x;
		cout << access.mechanic << " is working on " << unitNum << " " << makeModel << " at date of " << access.date << " with " << access.hrMi << " " << x << endl;
		cout << "\n 1) Oil Sample \n 2) Change Oil and Filters \n 3) Change Fuel Filters \n 4) Change Air Filters"
			<< "\n 5) Grease \n 6) Radiator \n 7) Transmission \n 8) Rears \n 9) Front Wheels \n 10) Tire Pressure \n 11) Lights \n 12) Brakes \n 13) Other \n";
		cout << "Choose a Number for the service you are doing: ";
	}
	else
	{
		menu();
	}
	serviceSwitch(makeModel, unitNum, access.mechanic, access.date, access.hrMi, x);

}

void serviceSwitch(string& makeModel, string& unitNum, string& mechanic, string& date, int& hrMi, string& x) {
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
		serviceSwitch(makeModel, unitNum, mechanic, date, hrMi, x);
	}
}