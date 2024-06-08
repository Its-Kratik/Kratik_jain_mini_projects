#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <limits>
#include <algorithm>
#include <iomanip> 
using namespace std;

struct Data {
    string agentId, contact, propertySize, roomType, location, sellingPrice;

    bool operator<(const Data& other) const {
        if (agentId == other.agentId) {
            return sellingPrice < other.sellingPrice;
        }
        return agentId < other.agentId;
    }
};

bool findPassword(string password, string id) {
    // Placeholder implementation
    return true;
}

bool login(string agentId, string password) {
    if (findPassword(password, agentId)) {
        cout << "Access granted" << endl;
        return true;
    } else {
        cout << "Login failed!" << endl;
        return false;
    }
}

void changePassword(string id) {
    // Prompt for current password
    // If login successful, prompt for new password
    // Update password file with new password
    // Implementation not shown
}

char getOption() {
    char option;
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    return tolower(option); // Convert to lowercase
}

void showMenu() {
    cout << "Menu:\n"
         << "(a) Add new property\n"
         << "(b) Remove property\n"
         << "(c) Edit property details\n"
         << "(d) Search properties\n"
         << "(e) Generate monthly report\n"
         << "(f) List properties in order\n"
         << "(i) Quit\n"
         << "Enter option: ";
}

void addProperty(list<Data>& propertyList) {
    Data newProperty;
    cout << "Enter Agent ID: ";
    getline(cin, newProperty.agentId);
    cout << "Enter Contact: ";
    getline(cin, newProperty.contact);
    cout << "Enter Property Size: ";
    getline(cin, newProperty.propertySize);
    cout << "Enter Room Type: ";
    getline(cin, newProperty.roomType);
    cout << "Enter Location: ";
    getline(cin, newProperty.location);
    cout << "Enter Selling Price: ";
    getline(cin, newProperty.sellingPrice);

    propertyList.push_back(newProperty);
    cout << "Property added successfully!" << endl;
}

void removeProperty(list<Data>& propertyList) {
    string agentId;
    cout << "Enter Agent ID of the property to remove: ";
    getline(cin, agentId);

    list<Data>::iterator it = find_if(propertyList.begin(), propertyList.end(), [&](const Data& data) {
        return data.agentId == agentId;
    });

    if (it != propertyList.end()) {
        propertyList.erase(it);
        cout << "Property removed successfully!" << endl;
    } else {
        cout << "Property with the given Agent ID not found." << endl;
    }
}

void editProperty(list<Data>& propertyList) {
    string agentId;
    cout << "Enter Agent ID of the property to edit: ";
    getline(cin, agentId);

    list<Data>::iterator it = find_if(propertyList.begin(), propertyList.end(), [&](const Data& data) {
        return data.agentId == agentId;
    });

    if (it != propertyList.end()) {
        cout << "Enter new property details:\n";
        cout << "Enter Contact: ";
        getline(cin, it->contact);
        cout << "Enter Property Size: ";
        getline(cin, it->propertySize);
        cout << "Enter Room Type: ";
        getline(cin, it->roomType);
        cout << "Enter Location: ";
        getline(cin, it->location);
        cout << "Enter Selling Price: ";
        getline(cin, it->sellingPrice);
        cout << "Property updated successfully!" << endl;
    } else {
        cout << "Property with the given Agent ID not found." << endl;
    }
}

void searchProperties(list<Data>& propertyList) {
    string searchTerm;
    cout << "Enter search term (Agent ID, Location, or Room Type): ";
    getline(cin, searchTerm);

    bool found = false;
    for (const Data& property : propertyList) {
        if (property.agentId == searchTerm ||
            property.location.find(searchTerm) != string::npos ||
            property.roomType.find(searchTerm) != string::npos) {
            cout << "Agent ID: " << property.agentId << "\n"
                 << "Contact: " << property.contact << "\n"
                 << "Property Size: " << property.propertySize << "\n"
                 << "Room Type: " << property.roomType << "\n"
                 << "Location: " << property.location << "\n"
                 << "Selling Price: " << property.sellingPrice << "\n\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No properties found matching the search term." << endl;
    }
}

void loadProperties(list<Data>& propertyList) {
    ifstream file("data.in");
    // Read property data from file and add to propertyList
    // Implementation not shown
    file.close();
}
void generateMonthlyReport(const list<Data>& propertyList) {
    int totalProperties = 0;
    double totalValue = 0.0;

    for (const Data& property : propertyList) {
        totalProperties++;
        totalValue += stod(property.sellingPrice);
    }

    double averagePrice = totalValue / totalProperties;

    cout << "Monthly Report:" << endl;
    cout << "Total Properties Listed: " << totalProperties << endl;
    cout << "Average Selling Price: $" << fixed << setprecision(2) << averagePrice << endl;
}


void showProperties(list<Data>& propertyList, char order) {
    if (order == 'a') {
        propertyList.sort(); // Sorts in ascending order by default
    } else if (order == 'd') {
        propertyList.sort();
        propertyList.reverse(); // Reverses the list for descending order
    }
    // Display properties
    for (const Data& property : propertyList) {
        cout << "Agent ID: " << property.agentId << "\n"
             << "Contact: " << property.contact << "\n"
             << "Property Size: " << property.propertySize << "\n"
             << "Room Type: " << property.roomType << "\n"
             << "Location: " << property.location << "\n"
             << "Selling Price: " << property.sellingPrice << "\n\n";
    }
}

int main() {
    list<Data> propertyList;
    string agentId, password;
    cout << "Enter Agent ID: ";
    getline(cin, agentId);
    cout << "Enter password: ";
    getline(cin, password);

    if (login(agentId, password)) {
        loadProperties(propertyList);
        char option;
        do {
            showMenu();
            option = getOption();
            switch (option) {
                case 'a':
                    addProperty(propertyList);
                    break;
                case 'b':
                    removeProperty(propertyList);
                    break;
                case 'c':
                    editProperty(propertyList);
                    break;
                case 'd':
                    searchProperties(propertyList);
                    break;
                case 'e':
                      generateMonthlyReport(propertyList);
                    break;
                case 'f':
                    char order;
                    cout << "Enter 'a' for ascending, 'd' for descending: ";
                    order = getOption();
                    showProperties(propertyList, order);
                    break;
                case 'i':
                    cout << "Goodbye" << endl;
                    break;
                default:
                    cout << "Invalid option" << endl;
            }
        } while (option!= 'i');
    }

    return 0;
}

