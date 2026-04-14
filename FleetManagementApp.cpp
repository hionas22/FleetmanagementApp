// Fleet Management software
// Version 2.0
//Last Updated 4/14/2026 7/30/2022
//Nicholas Hionas

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Truck {
    string unitNum;
    string makeModel;
    string serialNum;
    string plate;
};

struct Ticket {
    int workOrder = 0;
    string makeModel;
    string eqNum;
    string date;
    string issue;
    int hours = 0;
    int nextService = 0;
    string status;
};

namespace Files {
    const string trucks = "trucks.txt";
    const string tickets = "tickets.txt";
}

bool askYesNo(const string& prompt) {
    char answer{};
    cout << prompt;
    cin >> answer;
    return answer == 'y' || answer == 'Y';
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

vector<Truck> loadTrucks() {
    vector<Truck> trucks;
    ifstream file(Files::trucks);

    Truck truck;
    string dash1, dash2, dash3;
    while (file >> truck.unitNum >> dash1 >> truck.makeModel >> dash2 >> truck.serialNum >> dash3 >> truck.plate) {
        trucks.push_back(truck);
    }
    return trucks;
}

void saveTruck(const Truck& truck) {
    ofstream file(Files::trucks, ios::app);
    if (!file) {
        cerr << "Could not open trucks file for writing.\n";
        return;
    }

    file << '\n'
         << truck.unitNum << " - "
         << truck.makeModel << " - "
         << truck.serialNum << " - "
         << truck.plate;
}

void showTrucks(const vector<Truck>& trucks) {
    cout << "\nCurrent Equipment\n-----------------\n";
    for (const auto& truck : trucks) {
        cout << truck.unitNum << " - "
             << truck.makeModel << " - "
             << truck.serialNum << " - "
             << truck.plate << '\n';
    }
    cout << '\n';
}

const Truck* findTruckByUnit(const vector<Truck>& trucks, const string& unitNum) {
    for (const auto& truck : trucks) {
        if (truck.unitNum == unitNum) {
            return &truck;
        }
    }
    return nullptr;
}

vector<Ticket> loadTickets() {
    vector<Ticket> tickets;
    ifstream file(Files::tickets);

    string label;
    Ticket ticket;
    while (file >> label >> ticket.workOrder
                >> label >> ticket.makeModel
                >> label >> ticket.eqNum
                >> label >> ticket.date
                >> label >> ticket.issue
                >> label >> ticket.hours
                >> label >> ticket.nextService
                >> label >> ticket.status) {
        tickets.push_back(ticket);
    }

    return tickets;
}

int getNextWorkOrder(const vector<Ticket>& tickets) {
    int maxWorkOrder = 0;
    for (const auto& ticket : tickets) {
        if (ticket.workOrder > maxWorkOrder) {
            maxWorkOrder = ticket.workOrder;
        }
    }
    return maxWorkOrder + 1;
}

void appendTicket(const Ticket& ticket) {
    ofstream file(Files::tickets, ios::app);
    if (!file) {
        cerr << "Could not open tickets file for writing.\n";
        return;
    }

    file << "\nTicket: " << ticket.workOrder
         << " Machine: " << ticket.makeModel
         << " Equiptment#: " << ticket.eqNum
         << " Date: " << ticket.date
         << " Issue " << ticket.issue
         << " Current_Hr/Miles: " << ticket.hours
         << " Next_Service: " << ticket.nextService
         << " Status: " << ticket.status;
}

string getIssueStatus(const string& issue) {
    if (issue == "none" || issue == "None") return "NoProblems";
    if (issue == "needsService" || issue == "needsservice" || issue == "NeedsService") return "NeedsService";
    return "NeedsRepair";
}

void createTicket() {
    auto tickets = loadTickets();

    Ticket ticket;
    cout << "Enter MakeModel EquiptmentNumber Date Issue Hours NextService: ";
    cin >> ticket.makeModel >> ticket.eqNum >> ticket.date >> ticket.issue >> ticket.hours >> ticket.nextService;
    ticket.workOrder = getNextWorkOrder(tickets);
    ticket.status = getIssueStatus(ticket.issue);

    cout << "\nPreview\n-------\n";
    cout << "Ticket: " << ticket.workOrder
         << " Machine: " << ticket.makeModel
         << " Equiptment#: " << ticket.eqNum
         << " Date: " << ticket.date
         << " Issue " << ticket.issue
         << " Current_Hr/Miles: " << ticket.hours
         << " Next_Service: " << ticket.nextService
         << " Status: " << ticket.status << "\n\n";

    if (askYesNo("Save this ticket? (Y/N): ")) {
        appendTicket(ticket);
        cout << "Ticket saved.\n";
    }
}

void showTickets() {
    const auto tickets = loadTickets();
    if (tickets.empty()) {
        cout << "No tickets found.\n";
        return;
    }

    for (const auto& ticket : tickets) {
        cout << "Ticket: " << ticket.workOrder
             << " Machine: " << ticket.makeModel
             << " Equiptment#: " << ticket.eqNum
             << " Date: " << ticket.date
             << " Issue " << ticket.issue
             << " Current_Hr/Miles: " << ticket.hours
             << " Next_Service: " << ticket.nextService
             << " Status: " << ticket.status << '\n';
    }
}

void addTruck() {
    Truck truck;
    cout << "Enter Unit Number: ";
    cin >> truck.unitNum;
    cout << "Enter Make / Model: ";
    cin >> truck.makeModel;
    cout << "Enter Serial Number: ";
    cin >> truck.serialNum;
    cout << "Enter License Plate: ";
    cin >> truck.plate;

    saveTruck(truck);
    ofstream unitFile(truck.unitNum + truck.makeModel + ".txt", ios::app);
    cout << "Truck added successfully.\n";
}

void menu() {
    while (true) {
        auto trucks = loadTrucks();
        showTrucks(trucks);

        int choice = 0;
        cout << "1) Add New Equipment\n";
        cout << "2) Create Ticket\n";
        cout << "3) Show Tickets\n";
        cout << "4) Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTruck();
                break;
            case 2:
                createTicket();
                break;
            case 3:
                showTickets();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
}

int main() {
    menu();
    return 0;
}
