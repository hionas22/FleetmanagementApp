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
    string techName;
    string priority;
    string fixedBy;
    string partsUsed;
    double repairCost = 0.0;
};

namespace Files {
    const string trucks = "trucks.txt";
    const string tickets = "tickets.txt";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pauseScreen() {
    cout << "\nPress Enter to return...";
    cin.get();
}

bool askYesNo(const string& prompt) {
    char answer;
    cout << prompt;
    cin >> answer;
    clearInput();
    return answer == 'y' || answer == 'Y';
}

string getIssueStatus(const string& issue) {
    if (issue == "none" || issue == "None") return "NoProblems";
    if (issue == "needsService" || issue == "needsservice" || issue == "NeedsService") return "NeedsService";
    return "NeedsRepair";
}

vector<Truck> loadTrucks() {
    vector<Truck> trucks;
    ifstream file(Files::trucks);

    if (!file) return trucks;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Truck truck;

        getline(ss, truck.unitNum, '|');
        getline(ss, truck.makeModel, '|');
        getline(ss, truck.serialNum, '|');
        getline(ss, truck.plate, '|');

        if (!truck.unitNum.empty()) {
            trucks.push_back(truck);
        }
    }

    return trucks;
}

void saveTruck(const Truck& truck) {
    ofstream file(Files::trucks, ios::app);
    if (!file) {
        cerr << "Could not open trucks file for writing.\n";
        return;
    }

    file << truck.unitNum << '|'
        << truck.makeModel << '|'
        << truck.serialNum << '|'
        << truck.plate << '\n';
}

void showTrucks(const vector<Truck>& trucks) {
    cout << "Current Units\n";
    cout << "------------------------------------------------------------\n";

    if (trucks.empty()) {
        cout << "No equipment found.\n";
        return;
    }

    for (const auto& truck : trucks) {
        cout << "[" << truck.unitNum << "] "
            << truck.makeModel
            << " | Plate: " << truck.plate << '\n';
    }
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

    if (!file) return tickets;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Ticket ticket;
        string temp;

        try {
            getline(ss, temp, '|');
            if (temp.empty()) continue;
            ticket.workOrder = stoi(temp);

            getline(ss, ticket.makeModel, '|');
            getline(ss, ticket.eqNum, '|');
            getline(ss, ticket.date, '|');
            getline(ss, ticket.issue, '|');

            getline(ss, temp, '|');
            ticket.hours = temp.empty() ? 0 : stoi(temp);

            getline(ss, temp, '|');
            ticket.nextService = temp.empty() ? 0 : stoi(temp);

            getline(ss, ticket.status, '|');
            getline(ss, ticket.techName, '|');
            getline(ss, ticket.priority, '|');
            getline(ss, ticket.fixedBy, '|');
            getline(ss, ticket.partsUsed, '|');

            getline(ss, temp, '|');
            ticket.repairCost = temp.empty() ? 0.0 : stod(temp);

            if (ticket.makeModel.empty()) ticket.makeModel = "Unknown";
            if (ticket.eqNum.empty()) ticket.eqNum = "Unknown";
            if (ticket.date.empty()) ticket.date = "Unknown";
            if (ticket.issue.empty()) ticket.issue = "Unknown";
            if (ticket.status.empty()) ticket.status = "Open";
            if (ticket.techName.empty()) ticket.techName = "Unassigned";
            if (ticket.priority.empty()) ticket.priority = "Normal";
            if (ticket.fixedBy.empty()) ticket.fixedBy = "Not Closed";
            if (ticket.partsUsed.empty()) ticket.partsUsed = "None";

            tickets.push_back(ticket);
        }
        catch (...) {
            continue;
        }
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

    file << ticket.workOrder << '|'
        << ticket.makeModel << '|'
        << ticket.eqNum << '|'
        << ticket.date << '|'
        << ticket.issue << '|'
        << ticket.hours << '|'
        << ticket.nextService << '|'
        << ticket.status << '|'
        << ticket.techName << '|'
        << ticket.priority << '|'
        << ticket.fixedBy << '|'
        << ticket.partsUsed << '|'
        << ticket.repairCost << '\n';
}

void saveAllTickets(const vector<Ticket>& tickets) {
    ofstream file(Files::tickets);
    if (!file) {
        cerr << "Could not open tickets file for writing.\n";
        return;
    }

    for (const auto& ticket : tickets) {
        file << ticket.workOrder << '|'
            << ticket.makeModel << '|'
            << ticket.eqNum << '|'
            << ticket.date << '|'
            << ticket.issue << '|'
            << ticket.hours << '|'
            << ticket.nextService << '|'
            << ticket.status << '|'
            << ticket.techName << '|'
            << ticket.priority << '|'
            << ticket.fixedBy << '|'
            << ticket.partsUsed << '|'
            << ticket.repairCost << '\n';
    }
}

void showTickets() {
    vector<Ticket> tickets = loadTickets();

    cout << "\n============================================================\n";
    cout << "                        ALL TICKETS                         \n";
    cout << "============================================================\n";

    if (tickets.empty()) {
        cout << "No tickets found.\n";
        pauseScreen();
        return;
    }

    for (const auto& ticket : tickets) {
        cout << "Work Order    : " << ticket.workOrder << '\n';
        cout << "Unit Number   : " << ticket.eqNum << '\n';
        cout << "Machine       : " << ticket.makeModel << '\n';
        cout << "Date          : " << ticket.date << '\n';
        cout << "Issue         : " << ticket.issue << '\n';
        cout << "Tech          : " << ticket.techName << '\n';
        cout << "Priority      : " << ticket.priority << '\n';
        cout << "Hours/Miles   : " << ticket.hours << '\n';
        cout << "Next Service  : " << ticket.nextService << '\n';
        cout << "Status        : " << ticket.status << '\n';
        cout << "Fixed By      : " << ticket.fixedBy << '\n';
        cout << "Parts Used    : " << ticket.partsUsed << '\n';
        cout << "Repair Cost   : $" << ticket.repairCost << '\n';
        cout << "------------------------------------------------------------\n";
    }

    pauseScreen();
}

void showTicketsByUnit() {
    const auto tickets = loadTickets();

    if (tickets.empty()) {
        cout << "\nNo tickets found.\n";
        pauseScreen();
        return;
    }

    string unit;
    cout << "\nEnter Unit Number: ";
    getline(cin >> ws, unit);

    bool found = false;

    cout << "\n============================================================\n";
    cout << "                  TICKETS FOR UNIT " << unit << '\n';
    cout << "============================================================\n";

    for (const auto& ticket : tickets) {
        if (ticket.eqNum == unit) {
            found = true;

            cout << "Work Order    : " << ticket.workOrder << '\n';
            cout << "Unit Number   : " << ticket.eqNum << '\n';
            cout << "Machine       : " << ticket.makeModel << '\n';
            cout << "Date          : " << ticket.date << '\n';
            cout << "Issue         : " << ticket.issue << '\n';
            cout << "Tech          : " << ticket.techName << '\n';
            cout << "Priority      : " << ticket.priority << '\n';
            cout << "Hours/Miles   : " << ticket.hours << '\n';
            cout << "Next Service  : " << ticket.nextService << '\n';
            cout << "Status        : " << ticket.status << '\n';
            cout << "Fixed By      : " << ticket.fixedBy << '\n';
            cout << "Parts Used    : " << ticket.partsUsed << '\n';
            cout << "Repair Cost   : $" << ticket.repairCost << '\n';
            cout << "------------------------------------------------------------\n";
        }
    }

    if (!found) {
        cout << "No tickets found for that unit.\n";
    }

    pauseScreen();
}

void addTruck() {
    Truck truck;

    cout << "\nAdd New Equipment\n";
    cout << "-----------------\n";

    cout << "Enter Unit Number: ";
    getline(cin >> ws, truck.unitNum);

    cout << "Enter Make / Model: ";
    getline(cin >> ws, truck.makeModel);

    cout << "Enter Serial Number: ";
    getline(cin >> ws, truck.serialNum);

    cout << "Enter License Plate: ";
    getline(cin >> ws, truck.plate);

    saveTruck(truck);
    cout << "Equipment added successfully.\n";
    pauseScreen();
}

void createTicket() {
    auto tickets = loadTickets();
    auto trucks = loadTrucks();

    Ticket ticket;
    ticket.workOrder = getNextWorkOrder(tickets);

    cout << "\nCreate Ticket\n";
    cout << "-------------\n";

    cout << "Enter Equipment Number: ";
    getline(cin >> ws, ticket.eqNum);

    const Truck* truck = findTruckByUnit(trucks, ticket.eqNum);
    if (truck != nullptr) {
        ticket.makeModel = truck->makeModel;
        cout << "Matched Equipment: " << ticket.makeModel << '\n';
    }
    else {
        cout << "Equipment not found. Enter Make / Model manually: ";
        getline(cin >> ws, ticket.makeModel);
    }

    cout << "Enter Date: ";
    getline(cin >> ws, ticket.date);

    cout << "Enter Issue: ";
    getline(cin >> ws, ticket.issue);

    cout << "Enter Tech Name: ";
    getline(cin >> ws, ticket.techName);

    cout << "Enter Priority (Low / Normal / High / Emergency): ";
    getline(cin >> ws, ticket.priority);

    cout << "Enter Current Hours/Miles: ";
    while (!(cin >> ticket.hours)) {
        cout << "Invalid number. Enter Current Hours/Miles: ";
        clearInput();
    }
    clearInput();

    cout << "Enter Next Service: ";
    while (!(cin >> ticket.nextService)) {
        cout << "Invalid number. Enter Next Service: ";
        clearInput();
    }
    clearInput();

    ticket.fixedBy = "Not Closed";
    ticket.partsUsed = "None";
    ticket.repairCost = 0.0;
    ticket.status = getIssueStatus(ticket.issue);

    cout << "\nPreview\n";
    cout << "-------\n";
    cout << "Work Order: " << ticket.workOrder << '\n';
    cout << "Machine: " << ticket.makeModel << '\n';
    cout << "Equipment #: " << ticket.eqNum << '\n';
    cout << "Date: " << ticket.date << '\n';
    cout << "Issue: " << ticket.issue << '\n';
    cout << "Tech Name: " << ticket.techName << '\n';
    cout << "Priority: " << ticket.priority << '\n';
    cout << "Current Hours/Miles: " << ticket.hours << '\n';
    cout << "Next Service: " << ticket.nextService << '\n';
    cout << "Status: " << ticket.status << "\n\n";

    if (askYesNo("Save this ticket? (Y/N): ")) {
        appendTicket(ticket);
        cout << "Ticket saved.\n";
    }
    else {
        cout << "Ticket not saved.\n";
    }

    pauseScreen();
}

void closeTicket() {
    auto tickets = loadTickets();

    if (tickets.empty()) {
        cout << "\nNo tickets found.\n";
        pauseScreen();
        return;
    }

    int workOrder;
    cout << "\nEnter Work Order to close: ";

    while (!(cin >> workOrder)) {
        cout << "Invalid number. Enter Work Order to close: ";
        clearInput();
    }
    clearInput();

    for (auto& ticket : tickets) {
        if (ticket.workOrder == workOrder) {
            cout << "\nTicket found:\n";
            cout << "Work Order: " << ticket.workOrder << '\n';
            cout << "Machine: " << ticket.makeModel << '\n';
            cout << "Equipment #: " << ticket.eqNum << '\n';
            cout << "Date: " << ticket.date << '\n';
            cout << "Issue: " << ticket.issue << '\n';
            cout << "Assigned Tech: " << ticket.techName << '\n';
            cout << "Priority: " << ticket.priority << '\n';
            cout << "Current Status: " << ticket.status << "\n\n";

            if (ticket.status == "Closed") {
                cout << "This ticket is already closed.\n";
                pauseScreen();
                return;
            }

            if (askYesNo("Close this ticket? (Y/N): ")) {
                cout << "Enter who fixed it: ";
                getline(cin >> ws, ticket.fixedBy);

                cout << "Enter parts used: ";
                getline(cin >> ws, ticket.partsUsed);

                cout << "Enter repair price: ";
                while (!(cin >> ticket.repairCost)) {
                    cout << "Invalid number. Enter repair price: ";
                    clearInput();
                }
                clearInput();

                ticket.status = "Closed";
                saveAllTickets(tickets);
                cout << "Ticket closed successfully.\n";
            }
            else {
                cout << "Ticket was not changed.\n";
            }

            pauseScreen();
            return;
        }
    }

    cout << "Work order not found.\n";
    pauseScreen();
}

void unitMenu() {
    while (true) {
        int choice = 0;

        cout << "\nUnit Menu\n";
        cout << "---------\n";
        cout << "1) Show Tickets By Unit Number\n";
        cout << "2) Back to Main Menu\n";
        cout << "Choose: ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Choose: ";
            clearInput();
        }
        clearInput();

        switch (choice) {
        case 1:
            showTicketsByUnit();
            break;
        case 2:
            return;
        default:
            cout << "Invalid choice.\n\n";
            break;
        }
    }
}

int countClosedTickets(const vector<Ticket>& tickets) {
    int count = 0;
    for (const auto& ticket : tickets) {
        if (ticket.status == "Closed") {
            count++;
        }
    }
    return count;
}

int countOpenTickets(const vector<Ticket>& tickets) {
    int count = 0;
    for (const auto& ticket : tickets) {
        if (ticket.status != "Closed") {
            count++;
        }
    }
    return count;
}

double getTotalRepairCosts(const vector<Ticket>& tickets) {
    double total = 0.0;

    for (const auto& ticket : tickets) {
        if (ticket.status == "Closed") {
            total += ticket.repairCost;
        }
    }

    return total;
}

void showDashboard() {
    auto trucks = loadTrucks();
    auto tickets = loadTickets();

    int totalUnits = static_cast<int>(trucks.size());
    int totalTickets = static_cast<int>(tickets.size());
    int closedTickets = countClosedTickets(tickets);
    int openTickets = countOpenTickets(tickets);
    double totalRepairCosts = getTotalRepairCosts(tickets);

    cout << "\n============================================================\n";
    cout << "                 FLEET MANAGEMENT DASHBOARD                 \n";
    cout << "============================================================\n";
    cout << " Units in Fleet    : " << totalUnits << '\n';
    cout << " Total Tickets     : " << totalTickets << '\n';
    cout << " Open Tickets      : " << openTickets << '\n';
    cout << " Closed Tickets    : " << closedTickets << '\n';
    cout << " Maintenance Cost  : $" << totalRepairCosts << '\n';;
    cout << "============================================================\n";
    showTrucks(trucks);
    cout << "============================================================\n";
    cout << " 1) Add New Equipment\n";
    cout << " 2) Create Ticket\n";
    cout << " 3) Show Tickets\n";
    cout << " 4) Close Ticket\n";
    cout << " 5) Unit Menu\n";
    cout << " 6) Exit\n";
    cout << "============================================================\n";
}

void menu() {
    while (true) {
        int choice = 0;

        showDashboard();
        cout << "Choose: ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Choose: ";
            clearInput();
        }
        clearInput();

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
            closeTicket();
            break;
        case 5:
            unitMenu();
            break;
        case 6:
            cout << "Goodbye.\n";
            return;
        default:
            cout << "Invalid choice.\n\n";
            break;
        }
    }
}

int main() {
    menu();
    return 0;
}
