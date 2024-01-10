#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

const int MAX_RECORDS = 100;  // Maximum number of records
const int HASH_SIZE = 10;     // Size of the hash table

// Structure to store voter details
struct Voter {
    string voterID;
    string name;
    string address;
    int age;
    Voter* next;
};

// Function to calculate hash index
int calculateHashIndex(const string& voterID) {
    int sum = 0;
    for (char c : voterID) {
        sum += c;
    }
    return sum % HASH_SIZE;
}

// Function to add a new voter record
void addRecord(Voter* hashTable[], const string& voterID, const string& name, const string& address, int age) {
    int hashIndex = calculateHashIndex(voterID);

    // Create a new voter record
    Voter* newVoter = new Voter;
    newVoter->voterID = voterID;
    newVoter->name = name;
    newVoter->address = address;
    newVoter->age = age;
    newVoter->next = nullptr;

    // Insert the new voter record at the beginning of the linked list
    if (hashTable[hashIndex] == nullptr) {
        hashTable[hashIndex] = newVoter;
    } else {
        newVoter->next = hashTable[hashIndex];
        hashTable[hashIndex] = newVoter;
    }

    cout << "Record added successfully!" << endl;
}

// Function to search for a voter record
void searchRecord(Voter* hashTable[], const string& voterID) {
    int hashIndex = calculateHashIndex(voterID);

    // Traverse the linked list in the hash bucket
    Voter* current = hashTable[hashIndex];
    while (current != nullptr) {
        if (current->voterID == voterID) {
            cout << "Record found:" << endl;
            cout << "Voter ID: " << current->voterID << endl;
            cout << "Name: " << current->name << endl;
            cout << "Address: " << current->address << endl;
            cout << "Age: " << current->age << endl;
            return;
        }
        current = current->next;
    }

    cout << "Record not found!" << endl;
}

// Function to delete a voter record
void deleteRecord(Voter* hashTable[], const string& voterID) {
    int hashIndex = calculateHashIndex(voterID);

    // Handle the case when the record to be deleted is the first node in the linked list
    if (hashTable[hashIndex] != nullptr && hashTable[hashIndex]->voterID == voterID) {
        Voter* temp = hashTable[hashIndex];
        hashTable[hashIndex] = hashTable[hashIndex]->next;
        delete temp;
        cout << "Record deleted successfully!" << endl;
        return;
    }

    // Traverse the linked list in the hash bucket
    Voter* current = hashTable[hashIndex];
    while (current != nullptr && current->next != nullptr) {
        if (current->next->voterID == voterID) {
            Voter* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Record deleted successfully!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Record not found!" << endl;
}

// Function to update a voter record
void updateRecord(Voter* hashTable[], const string& voterID) {
    int hashIndex = calculateHashIndex(voterID);

    // Traverse the linked list in the hash bucket
    Voter* current = hashTable[hashIndex];
    while (current != nullptr) {
        if (current->voterID == voterID) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, current->name);
            cout << "Enter new address: ";
            getline(cin, current->address);
            cout << "Enter new age: ";
            cin >> current->age;
            cout << "Record updated successfully!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Record not found!" << endl;
}

// Function to display all voter records
void displayRecords(Voter* hashTable[]) {
    cout << "Voter Records:" << endl;
    for (int i = 0; i < HASH_SIZE; i++) {
        Voter* current = hashTable[i];
        while (current != nullptr) {
            cout << "Voter ID: " << current->voterID << endl;
            cout << "Name: " << current->name << endl;
            cout << "Address: " << current->address << endl;
            cout << "Age: " << current->age << endl;
            cout << "-------------------------" << endl;
            current = current->next;
        }
    }
}

// Function to display the menu
void displayMenu() {
    cout << "Voter ID Management System" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Search Record" << endl;
    cout << "3. Delete Record" << endl;
    cout << "4. Update Record" << endl;
    cout << "5. Display Records" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    Voter* hashTable[HASH_SIZE] = { nullptr };

    int choice;
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string voterID, name, address;
                int age;
                cout << "Enter Voter ID: ";
                cin >> voterID;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Address: ";
                getline(cin, address);
                cout << "Enter Age: ";
                cin >> age;
                addRecord(hashTable, voterID, name, address, age);
                break;
            }
            case 2: {
                string voterID;
                cout << "Enter Voter ID: ";
                cin >> voterID;
                searchRecord(hashTable, voterID);
                break;
            }
            case 3: {
                string voterID;
                cout << "Enter Voter ID: ";
                cin >> voterID;
                deleteRecord(hashTable, voterID);
                break;
            }
            case 4: {
                string voterID;
                cout << "Enter Voter ID: ";
                cin >> voterID;
                updateRecord(hashTable, voterID);
                break;
            }
            case 5:
                displayRecords(hashTable);
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice! Try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
