// Fleet Management software
// Version 2.0
//Last Updated 4/14/2026 7/30/2022
//Nicholas Hionas

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Truck {
    string unitNum;
    string makeModel;
    string serialNum;
    string plate;
    string customerId;
};

struct Customer {
    string customerId;
    string name;
    string phone;
    string email;
    string address;
    string company;
};

struct Ticket {
    int workOrder = 0;
    string makeModel;
    string eqNum;
    string customerId;
    string dateOpened;
    string issue;
    int hours = 0;
    int nextService = 0;
    string status;
    string assignedTech;
    string priority;
    string fixedBy;
    string partsUsed;
    double estimatedCost = 0.0;
    double repairCost = 0.0;
    string invoiceNumber;
    string paymentStatus;
};

struct User {
    string username;
    string password;
    string role;
};

struct Session {
    bool loggedIn = false;
    string username;
    string role;
};

namespace Files {
    const string trucks = "trucks.txt";
    const string tickets = "tickets.txt";
    const string users = "users.txt";
    const string customers = "customers.txt";
    const string backup = "fleet_backup.txt";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pauseScreen() {
    cout << "\nPress ENTER to continue...";
    cin.get();
}

bool askYesNo(const string& prompt) {
    char answer{};
    cout << prompt;
    cin >> answer;
    clearInput();
    return answer == 'y' || answer == 'Y';
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

string chooseRole() {
    while (true) {
        int choice = 0;
        cout << "\nSelect Role\n";
        cout << "1) Admin   - Full access\n";
        cout << "2) Tech    - Work tickets and updates\n";
        cout << "3) Viewer  - View only\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: return "Admin";
        case 2: return "Tech";
        case 3: return "Viewer";
        default: cout << "Invalid choice.\n";
        }
    }
}

string choosePriority() {
    while (true) {
        int choice = 0;
        cout << "\nPriority Guide\n";
        cout << "1) Low       - Not urgent\n";
        cout << "2) Normal    - Standard work\n";
        cout << "3) High      - Important, soon\n";
        cout << "4) Emergency - Immediate attention\n";
        cout << "Choose priority: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: return "Low";
        case 2: return "Normal";
        case 3: return "High";
        case 4: return "Emergency";
        default: cout << "Invalid choice.\n";
        }
    }
}

string choosePaymentStatus() {
    while (true) {
        int choice = 0;
        cout << "\nPayment Status\n";
        cout << "1) Unpaid\n";
        cout << "2) Paid\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: return "Unpaid";
        case 2: return "Paid";
        default: cout << "Invalid choice.\n";
        }
    }
}

bool hasAccess(const Session& session, const string& action) {
    if (!session.loggedIn) return false;
    if (session.role == "Admin") return true;

    if (session.role == "Tech") {
        return action == "dashboard" ||
            action == "showTickets" ||
            action == "showTicketsByUnit" ||
            action == "showUnitHistory" ||
            action == "searchCustomers" ||
            action == "searchUnits" ||
            action == "createTicket" ||
            action == "closeTicket" ||
            action == "updatePriority" ||
            action == "changeAssignedTech" ||
            action == "reports";
    }

    if (session.role == "Viewer") {
        return action == "dashboard" ||
            action == "showTickets" ||
            action == "showTicketsByUnit" ||
            action == "showUnitHistory" ||
            action == "searchCustomers" ||
            action == "searchUnits" ||
            action == "reports";
    }

    return false;
}

void denyAccess() {
    cout << "\nAccess denied.\n";
    pauseScreen();
}

string getIssueStatus(const string& issue) {
    string lower = issue;
    for (char& c : lower) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

    if (lower == "none") return "NoProblems";
    if (lower == "needsservice" || lower == "needs service") return "NeedsService";
    return "NeedsRepair";
}

vector<User> loadUsers() {
    vector<User> users;
    ifstream file(Files::users);
    if (!file) return users;

    string line;
    while (getline(file, line)) {
        if (trim(line).empty()) continue;

        stringstream ss(line);
        User u;
        getline(ss, u.username, '|');
        getline(ss, u.password, '|');
        getline(ss, u.role, '|');

        if (!u.username.empty()) users.push_back(u);
    }

    return users;
}

void saveUser(const User& user) {
    ofstream file(Files::users, ios::app);
    if (!file) {
        cerr << "Could not open users file for writing.\n";
        return;
    }

    file << user.username << '|'
        << user.password << '|'
        << user.role << '\n';
}

bool userExists(const vector<User>& users, const string& username) {
    for (const auto& user : users) {
        if (user.username == username) return true;
    }
    return false;
}

void ensureDefaultAdmin() {
    auto users = loadUsers();
    if (users.empty()) {
        saveUser({ "admin", "admin123", "Admin" });
    }
}

vector<Customer> loadCustomers() {
    vector<Customer> customers;
    ifstream file(Files::customers);
    if (!file) return customers;

    string line;
    while (getline(file, line)) {
        if (trim(line).empty()) continue;

        stringstream ss(line);
        Customer c;
        getline(ss, c.customerId, '|');
        getline(ss, c.name, '|');
        getline(ss, c.phone, '|');
        getline(ss, c.email, '|');
        getline(ss, c.address, '|');
        getline(ss, c.company, '|');

        if (!c.customerId.empty()) customers.push_back(c);
    }

    return customers;
}

void saveCustomer(const Customer& c) {
    ofstream file(Files::customers, ios::app);
    if (!file) {
        cerr << "Could not open customers file for writing.\n";
        return;
    }

    file << c.customerId << '|'
        << c.name << '|'
        << c.phone << '|'
        << c.email << '|'
        << c.address << '|'
        << c.company << '\n';
}

const Customer* findCustomerById(const vector<Customer>& customers, const string& customerId) {
    for (const auto& c : customers) {
        if (c.customerId == customerId) return &c;
    }
    return nullptr;
}

vector<Truck> loadTrucks() {
    vector<Truck> trucks;
    ifstream file(Files::trucks);
    if (!file) return trucks;

    string line;
    while (getline(file, line)) {
        if (trim(line).empty()) continue;

        stringstream ss(line);
        Truck t;
        getline(ss, t.unitNum, '|');
        getline(ss, t.makeModel, '|');
        getline(ss, t.serialNum, '|');
        getline(ss, t.plate, '|');
        getline(ss, t.customerId, '|');

        if (!t.unitNum.empty()) trucks.push_back(t);
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
        << truck.plate << '|'
        << truck.customerId << '\n';
}

const Truck* findTruckByUnit(const vector<Truck>& trucks, const string& unitNum) {
    for (const auto& truck : trucks) {
        if (truck.unitNum == unitNum) return &truck;
    }
    return nullptr;
}

vector<Ticket> loadTickets() {
    vector<Ticket> tickets;
    ifstream file(Files::tickets);
    if (!file) return tickets;

    string line;
    while (getline(file, line)) {
        if (trim(line).empty()) continue;

        stringstream ss(line);
        Ticket t;
        string temp;

        try {
            getline(ss, temp, '|');
            if (temp.empty()) continue;
            t.workOrder = stoi(temp);

            getline(ss, t.makeModel, '|');
            getline(ss, t.eqNum, '|');
            getline(ss, t.customerId, '|');
            getline(ss, t.dateOpened, '|');
            getline(ss, t.issue, '|');

            getline(ss, temp, '|');
            t.hours = temp.empty() ? 0 : stoi(temp);

            getline(ss, temp, '|');
            t.nextService = temp.empty() ? 0 : stoi(temp);

            getline(ss, t.status, '|');
            getline(ss, t.assignedTech, '|');
            getline(ss, t.priority, '|');
            getline(ss, t.fixedBy, '|');
            getline(ss, t.partsUsed, '|');

            getline(ss, temp, '|');
            t.estimatedCost = temp.empty() ? 0.0 : stod(temp);

            getline(ss, temp, '|');
            t.repairCost = temp.empty() ? 0.0 : stod(temp);

            getline(ss, t.invoiceNumber, '|');
            getline(ss, t.paymentStatus, '|');

            if (t.status.empty()) t.status = "Open";
            if (t.assignedTech.empty()) t.assignedTech = "Unassigned";
            if (t.priority.empty()) t.priority = "Normal";
            if (t.fixedBy.empty()) t.fixedBy = "Not Closed";
            if (t.partsUsed.empty()) t.partsUsed = "None";
            if (t.paymentStatus.empty()) t.paymentStatus = "Unpaid";

            tickets.push_back(t);
        }
        catch (...) {
            continue;
        }
    }

    return tickets;
}

void appendTicket(const Ticket& t) {
    ofstream file(Files::tickets, ios::app);
    if (!file) {
        cerr << "Could not open tickets file for writing.\n";
        return;
    }

    file << t.workOrder << '|'
        << t.makeModel << '|'
        << t.eqNum << '|'
        << t.customerId << '|'
        << t.dateOpened << '|'
        << t.issue << '|'
        << t.hours << '|'
        << t.nextService << '|'
        << t.status << '|'
        << t.assignedTech << '|'
        << t.priority << '|'
        << t.fixedBy << '|'
        << t.partsUsed << '|'
        << fixed << setprecision(2) << t.estimatedCost << '|'
        << fixed << setprecision(2) << t.repairCost << '|'
        << t.invoiceNumber << '|'
        << t.paymentStatus << '\n';
}

void saveAllTickets(const vector<Ticket>& tickets) {
    ofstream file(Files::tickets);
    if (!file) {
        cerr << "Could not open tickets file for writing.\n";
        return;
    }

    for (const auto& t : tickets) {
        file << t.workOrder << '|'
            << t.makeModel << '|'
            << t.eqNum << '|'
            << t.customerId << '|'
            << t.dateOpened << '|'
            << t.issue << '|'
            << t.hours << '|'
            << t.nextService << '|'
            << t.status << '|'
            << t.assignedTech << '|'
            << t.priority << '|'
            << t.fixedBy << '|'
            << t.partsUsed << '|'
            << fixed << setprecision(2) << t.estimatedCost << '|'
            << fixed << setprecision(2) << t.repairCost << '|'
            << t.invoiceNumber << '|'
            << t.paymentStatus << '\n';
    }
}

int getNextWorkOrder(const vector<Ticket>& tickets) {
    int maxWorkOrder = 0;
    for (const auto& t : tickets) {
        if (t.workOrder > maxWorkOrder) maxWorkOrder = t.workOrder;
    }
    return maxWorkOrder + 1;
}

int countClosedTickets(const vector<Ticket>& tickets) {
    int count = 0;
    for (const auto& t : tickets) {
        if (t.status == "Closed") count++;
    }
    return count;
}

int countOpenTickets(const vector<Ticket>& tickets) {
    int count = 0;
    for (const auto& t : tickets) {
        if (t.status != "Closed") count++;
    }
    return count;
}

double getTotalRepairCosts(const vector<Ticket>& tickets) {
    double total = 0.0;
    for (const auto& t : tickets) {
        if (t.status == "Closed") total += t.repairCost;
    }
    return total;
}

void createBackup() {
    ofstream out(Files::backup);
    if (!out) return;

    out << "=== USERS ===\n";
    ifstream users(Files::users);
    out << users.rdbuf();

    out << "\n=== CUSTOMERS ===\n";
    ifstream customers(Files::customers);
    out << customers.rdbuf();

    out << "\n=== TRUCKS ===\n";
    ifstream trucks(Files::trucks);
    out << trucks.rdbuf();

    out << "\n=== TICKETS ===\n";
    ifstream tickets(Files::tickets);
    out << tickets.rdbuf();
}

bool login(Session& session) {
    auto users = loadUsers();

    string username, password;
    cout << "\n============================================================\n";
    cout << "                         USER LOGIN                         \n";
    cout << "============================================================\n";
    cout << "Username: ";
    getline(cin >> ws, username);
    cout << "Password: ";
    getline(cin >> ws, password);

    for (const auto& u : users) {
        if (u.username == username && u.password == password) {
            session.loggedIn = true;
            session.username = u.username;
            session.role = u.role;
            cout << "\nLogin successful. Welcome, " << session.username
                << " (" << session.role << ").\n";
            pauseScreen();
            return true;
        }
    }

    cout << "\nInvalid username or password.\n";
    pauseScreen();
    return false;
}

void logout(Session& session) {
    session.loggedIn = false;
    session.username.clear();
    session.role.clear();
    cout << "\nLogged out successfully.\n";
    pauseScreen();
}

void addUser(const Session& session) {
    if (session.role != "Admin") {
        denyAccess();
        return;
    }

    auto users = loadUsers();
    User user;

    cout << "\nAdd New User\n";
    cout << "------------\n";
    cout << "Enter Username: ";
    getline(cin >> ws, user.username);

    if (userExists(users, user.username)) {
        cout << "That username already exists.\n";
        pauseScreen();
        return;
    }

    cout << "Enter Password: ";
    getline(cin >> ws, user.password);

    user.role = chooseRole();

    saveUser(user);
    cout << "User added successfully.\n";
    pauseScreen();
}

void addCustomer(const Session& session) {
    if (session.role != "Admin") {
        denyAccess();
        return;
    }

    Customer c;
    cout << "\nAdd Customer\n";
    cout << "------------\n";

    cout << "Customer ID: ";
    getline(cin >> ws, c.customerId);
    cout << "Name: ";
    getline(cin, c.name);
    cout << "Phone: ";
    getline(cin, c.phone);
    cout << "Email: ";
    getline(cin, c.email);
    cout << "Address: ";
    getline(cin, c.address);
    cout << "Company: ";
    getline(cin, c.company);

    saveCustomer(c);
    cout << "Customer added successfully.\n";
    pauseScreen();
}

void addTruck(const Session& session) {
    if (session.role != "Admin") {
        denyAccess();
        return;
    }

    auto customers = loadCustomers();
    Truck truck;

    cout << "\nAdd New Equipment\n";
    cout << "-----------------\n";
    cout << "Enter Unit Number: ";
    getline(cin >> ws, truck.unitNum);
    cout << "Enter Make / Model: ";
    getline(cin, truck.makeModel);
    cout << "Enter Serial Number: ";
    getline(cin, truck.serialNum);
    cout << "Enter License Plate: ";
    getline(cin, truck.plate);
    cout << "Enter Customer ID for this unit: ";
    getline(cin, truck.customerId);

    if (findCustomerById(customers, truck.customerId) == nullptr) {
        cout << "Warning: Customer ID not found. Equipment will still be saved.\n";
    }

    saveTruck(truck);
    cout << "Equipment added successfully.\n";
    pauseScreen();
}

void showCustomers(const Session& session) {
    if (!hasAccess(session, "searchCustomers")) {
        denyAccess();
        return;
    }

    auto customers = loadCustomers();
    cout << "\n====================== CUSTOMERS ===========================\n";

    if (customers.empty()) {
        cout << "No customers found.\n";
        pauseScreen();
        return;
    }

    for (const auto& c : customers) {
        cout << "Customer ID : " << c.customerId << '\n';
        cout << "Name        : " << c.name << '\n';
        cout << "Phone       : " << c.phone << '\n';
        cout << "Email       : " << c.email << '\n';
        cout << "Address     : " << c.address << '\n';
        cout << "Company     : " << c.company << '\n';
        cout << "------------------------------------------------------------\n";
    }

    pauseScreen();
}

void searchCustomers(const Session& session) {
    if (!hasAccess(session, "searchCustomers")) {
        denyAccess();
        return;
    }

    auto customers = loadCustomers();
    string term;

    cout << "\nSearch Customers\n";
    cout << "----------------\n";
    cout << "Enter Name / Phone / Company / ID: ";
    getline(cin >> ws, term);

    bool found = false;
    for (const auto& c : customers) {
        string haystack = c.customerId + " " + c.name + " " + c.phone + " " + c.company + " " + c.email;
        if (haystack.find(term) != string::npos) {
            found = true;
            cout << "Customer ID : " << c.customerId << '\n';
            cout << "Name        : " << c.name << '\n';
            cout << "Phone       : " << c.phone << '\n';
            cout << "Email       : " << c.email << '\n';
            cout << "Company     : " << c.company << '\n';
            cout << "------------------------------------------------------------\n";
        }
    }

    if (!found) cout << "No matching customers found.\n";
    pauseScreen();
}

void showUnits(const Session& session) {
    if (!hasAccess(session, "searchUnits")) {
        denyAccess();
        return;
    }

    auto trucks = loadTrucks();
    cout << "\n====================== EQUIPMENT ===========================\n";

    if (trucks.empty()) {
        cout << "No equipment found.\n";
        pauseScreen();
        return;
    }

    for (const auto& t : trucks) {
        cout << "Unit Number : " << t.unitNum << '\n';
        cout << "Make/Model  : " << t.makeModel << '\n';
        cout << "Serial No.  : " << t.serialNum << '\n';
        cout << "Plate       : " << t.plate << '\n';
        cout << "Customer ID : " << t.customerId << '\n';
        cout << "------------------------------------------------------------\n";
    }

    pauseScreen();
}

void searchUnits(const Session& session) {
    if (!hasAccess(session, "searchUnits")) {
        denyAccess();
        return;
    }

    auto trucks = loadTrucks();
    string term;

    cout << "\nSearch Equipment\n";
    cout << "----------------\n";
    cout << "Enter Unit / Make / Plate / Customer ID: ";
    getline(cin >> ws, term);

    bool found = false;
    for (const auto& t : trucks) {
        string haystack = t.unitNum + " " + t.makeModel + " " + t.plate + " " + t.customerId;
        if (haystack.find(term) != string::npos) {
            found = true;
            cout << "Unit Number : " << t.unitNum << '\n';
            cout << "Make/Model  : " << t.makeModel << '\n';
            cout << "Serial No.  : " << t.serialNum << '\n';
            cout << "Plate       : " << t.plate << '\n';
            cout << "Customer ID : " << t.customerId << '\n';
            cout << "------------------------------------------------------------\n";
        }
    }

    if (!found) cout << "No matching equipment found.\n";
    pauseScreen();
}

void createTicket(const Session& session) {
    if (!hasAccess(session, "createTicket")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    auto trucks = loadTrucks();

    Ticket t;
    t.workOrder = getNextWorkOrder(tickets);

    cout << "\nCreate Ticket\n";
    cout << "-------------\n";
    cout << "Work Order #: " << t.workOrder << '\n';

    cout << "Enter Equipment Number: ";
    getline(cin >> ws, t.eqNum);

    const Truck* truck = findTruckByUnit(trucks, t.eqNum);
    if (truck != nullptr) {
        t.makeModel = truck->makeModel;
        t.customerId = truck->customerId;
        cout << "Matched Equipment: " << t.makeModel << '\n';
        cout << "Linked Customer ID: " << t.customerId << '\n';
    }
    else {
        cout << "Equipment not found. Enter Make / Model manually: ";
        getline(cin, t.makeModel);
        cout << "Enter Customer ID manually: ";
        getline(cin, t.customerId);
    }

    cout << "Enter Date Opened: ";
    getline(cin >> ws, t.dateOpened);

    cout << "Enter Issue: ";
    getline(cin, t.issue);

    cout << "Enter Assigned Tech Name: ";
    getline(cin, t.assignedTech);

    t.priority = choosePriority();

    cout << "Enter Current Hours/Miles: ";
    while (!(cin >> t.hours)) {
        cout << "Invalid number. Enter Current Hours/Miles: ";
        clearInput();
    }
    clearInput();

    cout << "Enter Next Service: ";
    while (!(cin >> t.nextService)) {
        cout << "Invalid number. Enter Next Service: ";
        clearInput();
    }
    clearInput();

    cout << "Enter Estimated Cost: ";
    while (!(cin >> t.estimatedCost)) {
        cout << "Invalid number. Enter Estimated Cost: ";
        clearInput();
    }
    clearInput();

    t.status = getIssueStatus(t.issue);
    t.fixedBy = "Not Closed";
    t.partsUsed = "None";
    t.repairCost = 0.0;
    t.invoiceNumber = "Pending";
    t.paymentStatus = "Unpaid";

    cout << "\nPreview\n";
    cout << "-------\n";
    cout << "Work Order     : " << t.workOrder << '\n';
    cout << "Unit Number    : " << t.eqNum << '\n';
    cout << "Machine        : " << t.makeModel << '\n';
    cout << "Customer ID    : " << t.customerId << '\n';
    cout << "Date Opened    : " << t.dateOpened << '\n';
    cout << "Issue          : " << t.issue << '\n';
    cout << "Assigned Tech  : " << t.assignedTech << '\n';
    cout << "Priority       : " << t.priority << '\n';
    cout << "Hours/Miles    : " << t.hours << '\n';
    cout << "Next Service   : " << t.nextService << '\n';
    cout << "Estimated Cost : $" << fixed << setprecision(2) << t.estimatedCost << '\n';
    cout << "Status         : " << t.status << '\n';

    if (askYesNo("\nSave this ticket? (Y/N): ")) {
        appendTicket(t);
        cout << "Ticket saved.\n";
    }
    else {
        cout << "Ticket not saved.\n";
    }

    pauseScreen();
}

void printTicketBlock(const Ticket& t) {
    cout << "Work Order     : " << t.workOrder << '\n';
    cout << "Unit Number    : " << t.eqNum << '\n';
    cout << "Machine        : " << t.makeModel << '\n';
    cout << "Customer ID    : " << t.customerId << '\n';
    cout << "Date Opened    : " << t.dateOpened << '\n';
    cout << "Issue          : " << t.issue << '\n';
    cout << "Assigned Tech  : " << t.assignedTech << '\n';
    cout << "Priority       : " << t.priority << '\n';
    cout << "Hours/Miles    : " << t.hours << '\n';
    cout << "Next Service   : " << t.nextService << '\n';
    cout << "Status         : " << t.status << '\n';
    cout << "Fixed By       : " << t.fixedBy << '\n';
    cout << "Parts Used     : " << t.partsUsed << '\n';
    cout << "Estimated Cost : $" << fixed << setprecision(2) << t.estimatedCost << '\n';
    cout << "Repair Cost    : $" << fixed << setprecision(2) << t.repairCost << '\n';
    cout << "Invoice Number : " << t.invoiceNumber << '\n';
    cout << "Payment Status : " << t.paymentStatus << '\n';
    cout << "------------------------------------------------------------\n";
}

void showTickets(const Session& session) {
    if (!hasAccess(session, "showTickets")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    cout << "\n====================== ALL TICKETS =========================\n";

    if (tickets.empty()) {
        cout << "No tickets found.\n";
        pauseScreen();
        return;
    }

    for (const auto& t : tickets) {
        printTicketBlock(t);
    }

    pauseScreen();
}

void showTicketsByUnit(const Session& session) {
    if (!hasAccess(session, "showTicketsByUnit")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    string unit;
    cout << "\nEnter Unit Number: ";
    getline(cin >> ws, unit);

    bool found = false;
    cout << "\n================== TICKETS FOR UNIT " << unit << " ==================\n";

    for (const auto& t : tickets) {
        if (t.eqNum == unit) {
            found = true;
            printTicketBlock(t);
        }
    }

    if (!found) cout << "No tickets found for that unit.\n";
    pauseScreen();
}

void showUnitHistory(const Session& session) {
    if (!hasAccess(session, "showUnitHistory")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    string unit;
    cout << "\nEnter Unit Number for Service History: ";
    getline(cin >> ws, unit);

    bool found = false;
    double totalSpent = 0.0;

    cout << "\n================= SERVICE HISTORY FOR UNIT " << unit << " =================\n";
    for (const auto& t : tickets) {
        if (t.eqNum == unit) {
            found = true;
            printTicketBlock(t);
            if (t.status == "Closed") totalSpent += t.repairCost;
        }
    }

    if (!found) {
        cout << "No service history found for that unit.\n";
    }
    else {
        cout << "Total Lifetime Repair Cost for Unit " << unit
            << " : $" << fixed << setprecision(2) << totalSpent << '\n';
    }

    pauseScreen();
}

void closeTicket(const Session& session) {
    if (!hasAccess(session, "closeTicket")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    if (tickets.empty()) {
        cout << "\nNo tickets found.\n";
        pauseScreen();
        return;
    }

    int workOrder;
    cout << "\nEnter Work Order to close: ";
    while (!(cin >> workOrder)) {
        cout << "Invalid number. Enter Work Order: ";
        clearInput();
    }
    clearInput();

    for (auto& t : tickets) {
        if (t.workOrder == workOrder) {
            cout << "\nTicket found:\n";
            printTicketBlock(t);

            if (t.status == "Closed") {
                cout << "This ticket is already closed.\n";
                pauseScreen();
                return;
            }

            if (askYesNo("Close this ticket? (Y/N): ")) {
                cout << "Enter who fixed it: ";
                getline(cin >> ws, t.fixedBy);

                cout << "Enter parts used: ";
                getline(cin, t.partsUsed);

                cout << "Enter final repair cost: ";
                while (!(cin >> t.repairCost)) {
                    cout << "Invalid number. Enter final repair cost: ";
                    clearInput();
                }
                clearInput();

                cout << "Enter invoice number: ";
                getline(cin >> ws, t.invoiceNumber);

                t.paymentStatus = choosePaymentStatus();
                t.status = "Closed";

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

void updateTicketPriority(const Session& session) {
    if (!hasAccess(session, "updatePriority")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    int workOrder;

    cout << "\nEnter Work Order to update priority: ";
    while (!(cin >> workOrder)) {
        cout << "Invalid number. Enter Work Order: ";
        clearInput();
    }
    clearInput();

    for (auto& t : tickets) {
        if (t.workOrder == workOrder) {
            cout << "Current Priority: " << t.priority << '\n';
            t.priority = choosePriority();
            saveAllTickets(tickets);
            cout << "Priority updated successfully.\n";
            pauseScreen();
            return;
        }
    }

    cout << "Work order not found.\n";
    pauseScreen();
}

void changeAssignedTech(const Session& session) {
    if (!hasAccess(session, "changeAssignedTech")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    int workOrder;

    cout << "\nEnter Work Order to change assigned tech: ";
    while (!(cin >> workOrder)) {
        cout << "Invalid number. Enter Work Order: ";
        clearInput();
    }
    clearInput();

    for (auto& t : tickets) {
        if (t.workOrder == workOrder) {
            cout << "Current Assigned Tech: " << t.assignedTech << '\n';
            cout << "Enter new Assigned Tech: ";
            getline(cin >> ws, t.assignedTech);
            saveAllTickets(tickets);
            cout << "Assigned tech updated successfully.\n";
            pauseScreen();
            return;
        }
    }

    cout << "Work order not found.\n";
    pauseScreen();
}

struct UnitCostReport {
    string unitNum;
    string makeModel;
    double totalCost = 0.0;
    int closedTickets = 0;
};

void showMostExpensiveUnitsReport(const Session& session) {
    if (!hasAccess(session, "reports")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    map<string, UnitCostReport> unitTotals;

    for (const auto& t : tickets) {
        auto& entry = unitTotals[t.eqNum];
        entry.unitNum = t.eqNum;
        entry.makeModel = t.makeModel;

        if (t.status == "Closed") {
            entry.totalCost += t.repairCost;
            entry.closedTickets++;
        }
    }

    vector<UnitCostReport> report;
    for (const auto& pair : unitTotals) report.push_back(pair.second);

    sort(report.begin(), report.end(),
        [](const UnitCostReport& a, const UnitCostReport& b) {
            return a.totalCost > b.totalCost;
        });

    cout << "\n================ MOST EXPENSIVE UNITS ======================\n";
    if (report.empty()) {
        cout << "No data.\n";
        pauseScreen();
        return;
    }

    cout << left
        << setw(12) << "Unit"
        << setw(25) << "Machine"
        << setw(15) << "Closed Jobs"
        << setw(15) << "Total Cost" << '\n';
    cout << "------------------------------------------------------------\n";

    for (const auto& item : report) {
        cout << left
            << setw(12) << item.unitNum
            << setw(25) << item.makeModel
            << setw(15) << item.closedTickets
            << "$" << fixed << setprecision(2) << item.totalCost << '\n';
    }

    pauseScreen();
}

void showOpenTicketsBoard(const Session& session) {
    if (!hasAccess(session, "reports")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    cout << "\n=================== OPEN TICKETS BOARD =====================\n";

    bool found = false;
    for (const auto& t : tickets) {
        if (t.status != "Closed") {
            found = true;
            cout << "WO#" << t.workOrder
                << " | Unit " << t.eqNum
                << " | " << t.makeModel
                << " | Tech: " << t.assignedTech
                << " | Priority: " << t.priority
                << " | Status: " << t.status << '\n';
        }
    }

    if (!found) cout << "No open tickets.\n";
    pauseScreen();
}

void showPriorityReport(const Session& session) {
    if (!hasAccess(session, "reports")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    cout << "\n==================== PRIORITY REPORT =======================\n";

    vector<Ticket> emergency, high, normal, low;
    for (const auto& t : tickets) {
        if (t.status == "Closed") continue;
        if (t.priority == "Emergency") emergency.push_back(t);
        else if (t.priority == "High") high.push_back(t);
        else if (t.priority == "Low") low.push_back(t);
        else normal.push_back(t);
    }

    auto printGroup = [](const string& title, const vector<Ticket>& group) {
        cout << "\n" << title << '\n';
        cout << "------------------------------------------------------------\n";
        if (group.empty()) {
            cout << "None\n";
            return;
        }
        for (const auto& t : group) {
            cout << "WO#" << t.workOrder
                << " | Unit " << t.eqNum
                << " | " << t.makeModel
                << " | Tech: " << t.assignedTech
                << " | Status: " << t.status << '\n';
        }
        };

    printGroup("Emergency", emergency);
    printGroup("High", high);
    printGroup("Normal", normal);
    printGroup("Low", low);

    pauseScreen();
}

void showTechWorkloadReport(const Session& session) {
    if (!hasAccess(session, "reports")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    map<string, int> openByTech;
    map<string, int> closedByTech;
    set<string> techs;

    for (const auto& t : tickets) {
        string tech = t.assignedTech.empty() ? "Unassigned" : t.assignedTech;
        techs.insert(tech);

        if (t.status == "Closed") closedByTech[tech]++;
        else openByTech[tech]++;
    }

    cout << "\n=================== TECH WORKLOAD REPORT ===================\n";
    if (techs.empty()) {
        cout << "No tech data found.\n";
        pauseScreen();
        return;
    }

    cout << left
        << setw(24) << "Tech"
        << setw(15) << "Open Jobs"
        << setw(15) << "Closed Jobs" << '\n';
    cout << "------------------------------------------------------------\n";

    for (const auto& tech : techs) {
        cout << left
            << setw(24) << tech
            << setw(15) << openByTech[tech]
            << setw(15) << closedByTech[tech] << '\n';
    }

    pauseScreen();
}

void showRepairSpendingByUnit(const Session& session) {
    if (!hasAccess(session, "reports")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    map<string, double> spending;
    map<string, string> machineNames;

    for (const auto& t : tickets) {
        if (t.status == "Closed") {
            spending[t.eqNum] += t.repairCost;
            machineNames[t.eqNum] = t.makeModel;
        }
    }

    cout << "\n================== REPAIR SPENDING BY UNIT =================\n";
    if (spending.empty()) {
        cout << "No closed repair costs found.\n";
        pauseScreen();
        return;
    }

    for (const auto& pair : spending) {
        cout << "Unit: " << pair.first
            << " | Machine: " << machineNames[pair.first]
            << " | Total: $" << fixed << setprecision(2) << pair.second << '\n';
    }

    pauseScreen();
}

void exportTicketsCSV(const Session& session) {
    if (!hasAccess(session, "reports")) {
        denyAccess();
        return;
    }

    auto tickets = loadTickets();
    ofstream file("tickets_export.csv");
    if (!file) {
        cout << "Could not create tickets_export.csv\n";
        pauseScreen();
        return;
    }

    file << "WorkOrder,MakeModel,Unit,CustomerID,DateOpened,Issue,Hours,NextService,Status,AssignedTech,Priority,FixedBy,PartsUsed,EstimatedCost,RepairCost,InvoiceNumber,PaymentStatus\n";

    for (const auto& t : tickets) {
        file << t.workOrder << ','
            << '"' << t.makeModel << '"' << ','
            << '"' << t.eqNum << '"' << ','
            << '"' << t.customerId << '"' << ','
            << '"' << t.dateOpened << '"' << ','
            << '"' << t.issue << '"' << ','
            << t.hours << ','
            << t.nextService << ','
            << '"' << t.status << '"' << ','
            << '"' << t.assignedTech << '"' << ','
            << '"' << t.priority << '"' << ','
            << '"' << t.fixedBy << '"' << ','
            << '"' << t.partsUsed << '"' << ','
            << fixed << setprecision(2) << t.estimatedCost << ','
            << fixed << setprecision(2) << t.repairCost << ','
            << '"' << t.invoiceNumber << '"' << ','
            << '"' << t.paymentStatus << '"' << '\n';
    }

    cout << "Exported tickets to tickets_export.csv\n";
    pauseScreen();
}

void reportsMenu(const Session& session) {
    if (!hasAccess(session, "reports")) {
        denyAccess();
        return;
    }

    while (true) {
        int choice = 0;
        cout << "\n====================== REPORTS MENU ========================\n";
        cout << "1) Most Expensive Units\n";
        cout << "2) Open Tickets Board\n";
        cout << "3) Priority Report\n";
        cout << "4) Tech Workload Report\n";
        cout << "5) Repair Spending By Unit\n";
        cout << "6) Export Tickets CSV\n";
        cout << "7) Create Backup File\n";
        cout << "8) Back\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: showMostExpensiveUnitsReport(session); break;
        case 2: showOpenTicketsBoard(session); break;
        case 3: showPriorityReport(session); break;
        case 4: showTechWorkloadReport(session); break;
        case 5: showRepairSpendingByUnit(session); break;
        case 6: exportTicketsCSV(session); break;
        case 7:
            createBackup();
            cout << "Backup saved to " << Files::backup << '\n';
            pauseScreen();
            break;
        case 8: return;
        default: cout << "Invalid choice.\n";
        }
    }
}

void unitMenu(const Session& session) {
    while (true) {
        int choice = 0;
        cout << "\n======================= UNIT MENU ==========================\n";
        cout << "1) Show Tickets By Unit Number\n";
        cout << "2) Show Unit Service History\n";
        cout << "3) Show All Equipment\n";
        cout << "4) Search Equipment\n";
        cout << "5) Back\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: showTicketsByUnit(session); break;
        case 2: showUnitHistory(session); break;
        case 3: showUnits(session); break;
        case 4: searchUnits(session); break;
        case 5: return;
        default: cout << "Invalid choice.\n";
        }
    }
}

void customerMenu(const Session& session) {
    while (true) {
        int choice = 0;
        cout << "\n===================== CUSTOMER MENU ========================\n";
        cout << "1) Add Customer\n";
        cout << "2) Show All Customers\n";
        cout << "3) Search Customers\n";
        cout << "4) Back\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: addCustomer(session); break;
        case 2: showCustomers(session); break;
        case 3: searchCustomers(session); break;
        case 4: return;
        default: cout << "Invalid choice.\n";
        }
    }
}

void showDashboard(const Session& session) {
    auto trucks = loadTrucks();
    auto tickets = loadTickets();
    auto customers = loadCustomers();

    cout << "\n============================================================\n";
    cout << "                 FLEET MANAGEMENT DASHBOARD                 \n";
    cout << "============================================================\n";
    cout << " User              : " << session.username << '\n';
    cout << " Role              : " << session.role << '\n';
    cout << " Units in Fleet    : " << trucks.size() << '\n';
    cout << " Customers         : " << customers.size() << '\n';
    cout << " Total Tickets     : " << tickets.size() << '\n';
    cout << " Open Tickets      : " << countOpenTickets(tickets) << '\n';
    cout << " Closed Tickets    : " << countClosedTickets(tickets) << '\n';
    cout << " Repair Spending   : $" << fixed << setprecision(2) << getTotalRepairCosts(tickets) << '\n';
    cout << "============================================================\n";
    cout << " 1) Add New Equipment\n";
    cout << " 2) Create Ticket\n";
    cout << " 3) Show Tickets\n";
    cout << " 4) Close Ticket\n";
    cout << " 5) Unit Menu\n";
    cout << " 6) Reports\n";
    cout << " 7) Update Ticket Priority\n";
    cout << " 8) Change Assigned Tech\n";
    cout << " 9) Customer Menu\n";
    cout << " 10) Add User\n";
    cout << " 11) Logout\n";
    cout << " 12) Exit\n";
    cout << "============================================================\n";
}

void mainMenu(Session& session) {
    while (session.loggedIn) {
        int choice = 0;
        showDashboard(session);
        cout << "Choose: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: addTruck(session); break;
        case 2: createTicket(session); break;
        case 3: showTickets(session); break;
        case 4: closeTicket(session); break;
        case 5: unitMenu(session); break;
        case 6: reportsMenu(session); break;
        case 7: updateTicketPriority(session); break;
        case 8: changeAssignedTech(session); break;
        case 9: customerMenu(session); break;
        case 10:
            if (session.role == "Admin") addUser(session);
            else denyAccess();
            break;
        case 11:
            logout(session);
            return;
        case 12:
            cout << "Goodbye.\n";
            exit(0);
        default:
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    ensureDefaultAdmin();

    while (true) {
        Session session;
        if (login(session)) {
            mainMenu(session);
        }
    }

    return 0;
}
