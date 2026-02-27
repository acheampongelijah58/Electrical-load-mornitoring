#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_APPLIANCES = 100;

// =========================
// Appliance Class
// =========================
class Appliance {
private:
    string name;
    double powerRating;  // Watts
    double usageHours;   // Hours per day

public:
    Appliance() {
        name = "";
        powerRating = 0;
        usageHours = 0;
    }

    void setData(string n, double p, double u) {
        name = n;
        powerRating = p;
        usageHours = u;
    }

    string getName() const {
        return name;
    }

    double getPower() const {
        return powerRating;
    }

    double getUsage() const {
        return usageHours;
    }

    double calculateEnergy() const {
        return (powerRating * usageHours) / 1000.0;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Power Rating: " << powerRating << " W" << endl;
        cout << "Usage Hours: " << usageHours << " hrs/day" << endl;
        cout << "Daily Energy: " << calculateEnergy() << " kWh" << endl;
        cout << "-----------------------------" << endl;
    }
};

// =========================
// Function Prototypes
// =========================
void registerAppliance(Appliance appliances[], int &count);
void viewAppliances(Appliance appliances[], int count);
void searchAppliance(Appliance appliances[], int count);
double calculateTotalEnergy(Appliance appliances[], int count);
void calculateBill(Appliance appliances[], int count);
void saveToFile(Appliance appliances[], int count);
void loadFromFile(Appliance appliances[], int &count);

// =========================
// Main Function
// =========================
int main() {
    Appliance appliances[MAX_APPLIANCES];
    int applianceCount = 0;

    loadFromFile(appliances, applianceCount);

    int choice;

    do {
        cout << "\n===== ELECTRICAL LOAD MONITORING SYSTEM =====\n";
        cout << "1. Register Appliance\n";
        cout << "2. View All Appliances\n";
        cout << "3. Search Appliance\n";
        cout << "4. Calculate Total Energy\n";
        cout << "5. Calculate Bill\n";
        cout << "6. Save Data\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }

        switch(choice) {
            case 1:
                registerAppliance(appliances, applianceCount);
                break;
            case 2:
                viewAppliances(appliances, applianceCount);
                break;
            case 3:
                searchAppliance(appliances, applianceCount);
                break;
            case 4:
                cout << "Total Energy Consumption: "
                     << calculateTotalEnergy(appliances, applianceCount)
                     << " kWh\n";
                break;
            case 5:
                calculateBill(appliances, applianceCount);
                break;
            case 6:
                saveToFile(appliances, applianceCount);
                break;
            case 7:
                saveToFile(appliances, applianceCount);
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please select 1-7.\n";
        }

    } while(choice != 7);

    return 0;
}

// =========================
// Register Appliance
// =========================
void registerAppliance(Appliance appliances[], int &count) {

    if(count >= MAX_APPLIANCES) {
        cout << "Maximum appliance limit reached!\n";
        return;
    }

    string name;
    double power, hours;

    cout << "Enter appliance name: ";
    cin.ignore();
    getline(cin, name);

    if(name.empty()) {
        cout << "Appliance name cannot be empty!\n";
        return;
    }

    cout << "Enter power rating (Watts): ";
    cin >> power;
    if(power <= 0) {
        cout << "Power must be greater than zero!\n";
        return;
    }

    cout << "Enter usage hours per day (0-24): ";
    cin >> hours;
    if(hours < 0 || hours > 24) {
        cout << "Usage hours must be between 0 and 24!\n";
        return;
    }

    appliances[count].setData(name, power, hours);
    count++;

    cout << "Appliance registered successfully!\n";
}

// =========================
// View Appliances
// =========================
void viewAppliances(Appliance appliances[], int count) {

    if(count == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    for(int i = 0; i < count; i++) {
        appliances[i].display();
    }
}

// =========================
// Search Appliance
// =========================
void searchAppliance(Appliance appliances[], int count) {

    if(count == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    string searchName;
    cout << "Enter appliance name to search: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;

    for(int i = 0; i < count; i++) {
        if(appliances[i].getName() == searchName) {
            appliances[i].display();
            found = true;
        }
    }

    if(!found) {
        cout << "Appliance not found.\n";
    }
}

// =========================
// Calculate Total Energy
// =========================
double calculateTotalEnergy(Appliance appliances[], int count) {

    double total = 0;

    for(int i = 0; i < count; i++) {
        total += appliances[i].calculateEnergy();
    }

    return total;
}

// =========================
// Calculate Bill
// =========================
void calculateBill(Appliance appliances[], int count) {

    if(count == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    double tariff;
    cout << "Enter electricity tariff per kWh: ";
    cin >> tariff;

    if(tariff <= 0) {
        cout << "Tariff must be positive!\n";
        return;
    }

    double totalEnergy = calculateTotalEnergy(appliances, count);
    double totalCost = totalEnergy * tariff;

    cout << fixed << setprecision(2);
    cout << "\n========== BILLING SUMMARY ==========\n";

    for(int i = 0; i < count; i++) {
        cout << appliances[i].getName() << " : "
             << appliances[i].calculateEnergy() << " kWh\n";
    }

    cout << "--------------------------------------\n";
    cout << "Total Energy: " << totalEnergy << " kWh\n";
    cout << "Tariff: " << tariff << " per kWh\n";
    cout << "Total Cost: " << totalCost << endl;
    cout << "======================================\n";

    ofstream billFile("billing_summary.txt");
    billFile << "Total Energy: " << totalEnergy << " kWh\n";
    billFile << "Tariff: " << tariff << endl;
    billFile << "Total Cost: " << totalCost << endl;
    billFile.close();
}

// =========================
// Save to File
// =========================
void saveToFile(Appliance appliances[], int count) {

    ofstream file("appliances.txt");

    for(int i = 0; i < count; i++) {
        file << appliances[i].getName() << " "
             << appliances[i].getPower() << " "
             << appliances[i].getUsage() << endl;
    }

    file.close();
    cout << "Data saved successfully.\n";
}

// =========================
// Load From File
// =========================
void loadFromFile(Appliance appliances[], int &count) {

    ifstream file("appliances.txt");

    string name;
    double power, usage;

    while(file >> name >> power >> usage) {
        appliances[count].setData(name, power, usage);
        count++;
    }

    file.close();
}