#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class
class Vehicle {
protected:
    string vehicleID;
    string brand;
    string model;
    double rentPerDay;
    bool isAvailable;

public:
    Vehicle(string id, string b, string m, double rent)
        : vehicleID(id), brand(b), model(m), rentPerDay(rent), isAvailable(true) {}

    virtual void displayDetails() {
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Rent per day: ₹" << rentPerDay << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    bool getAvailability() { return isAvailable; }
    string getID() { return vehicleID; }
    double getRent() { return rentPerDay; }

    void rentVehicle() { isAvailable = false; }
    void returnVehicle() { isAvailable = true; }

    virtual ~Vehicle() {}
};

// Derived classes
class Car : public Vehicle {
    int seatingCapacity;
public:
    Car(string id, string b, string m, double rent, int seats)
        : Vehicle(id, b, m, rent), seatingCapacity(seats) {}

    void displayDetails() override {
        cout << "----- Car Details -----" << endl;
        Vehicle::displayDetails();
        cout << "Seating Capacity: " << seatingCapacity << " seats" << endl;
        cout << "-----------------------" << endl;
    }
};

class Bike : public Vehicle {
    string type;
public:
    Bike(string id, string b, string m, double rent, string t)
        : Vehicle(id, b, m, rent), type(t) {}

    void displayDetails() override {
        cout << "----- Bike Details -----" << endl;
        Vehicle::displayDetails();
        cout << "Type: " << type << endl;
        cout << "------------------------" << endl;
    }
};

// Customer class
class Customer {
    string name;
    string contact;
public:
    Customer(string n, string c) : name(n), contact(c) {}
    void displayInfo() {
        cout << "Customer Name: " << name << endl;
        cout << "Contact: " << contact << endl;
    }
};

// Rental Management class
class RentalSystem {
    vector<Vehicle*> vehicles;

public:
    void addVehicle(Vehicle* v) {
        vehicles.push_back(v);
    }

    void showAvailableVehicles() {
        cout << "\n--- Available Vehicles ---\n";
        for (auto v : vehicles) {
            if (v->getAvailability())
                v->displayDetails();
        }
    }

    void rentVehicle(string id, Customer &cust, int days) {
        for (auto v : vehicles) {
            if (v->getID() == id && v->getAvailability()) {
                cout << "\nVehicle rented successfully!" << endl;
                v->rentVehicle();
                cust.displayInfo();
                cout << "Total Rent: ₹" << v->getRent() * days << " for " << days << " days.\n";
                return;
            }
        }
        cout << "Sorry, Vehicle not available or invalid ID.\n";
    }

    void returnVehicle(string id) {
        for (auto v : vehicles) {
            if (v->getID() == id) {
                v->returnVehicle();
                cout << "Vehicle returned successfully!\n";
                return;
            }
        }
        cout << "Invalid Vehicle ID.\n";
    }

    ~RentalSystem() {
        for (auto v : vehicles)
            delete v;
    }
};

// Main function
int main() {
    RentalSystem system;

    // Adding vehicles
    system.addVehicle(new Car("C101", "Toyota", "Innova", 2500, 7));
    system.addVehicle(new Car("C102", "Hyundai", "i20", 1800, 5));
    system.addVehicle(new Bike("B201", "Royal Enfield", "Classic 350", 900, "Cruiser"));
    system.addVehicle(new Bike("B202", "Yamaha", "R15", 1200, "Sport"));

    cout << "===== Vehicle Rental System =====\n";

    Customer cust("Ankit", "9876543210");

    int choice;
    do {
        cout << "\n1. Show Available Vehicles";
        cout << "\n2. Rent a Vehicle";
        cout << "\n3. Return a Vehicle";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.showAvailableVehicles();
            break;
        case 2: {
            string id;
            int days;
            cout << "Enter Vehicle ID to rent: ";
            cin >> id;
            cout << "Enter number of days: ";
            cin >> days;
            system.rentVehicle(id, cust, days);
            break;
        }
        case 3: {
            string id;
            cout << "Enter Vehicle ID to return: ";
            cin >> id;
            system.returnVehicle(id);
            break;
        }
        case 4:
            cout << "Thank you for using the Vehicle Rental System!\n";z
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}