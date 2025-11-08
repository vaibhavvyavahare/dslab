#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 

using namespace std;

// Define a fixed-size structure for direct access file organization
struct Student {
    int id; 
    char name[50]; 
    char major[50]; 
    bool isActive; 
};

const string FILENAME = "students.dat";
const int RECORD_SIZE = sizeof(Student);

// UTILITY: Get record offset in bytes
long getRecordOffset(int recordNumber) {
    return (long)(recordNumber - 1) * RECORD_SIZE;
}

// CREATE OPERATION
void addRecord() {
    Student newStudent;
    
    ifstream infile(FILENAME, ios::binary | ios::ate);
    long fileSize = infile.tellg();
    infile.close();
    
    newStudent.id = (fileSize / RECORD_SIZE) + 1;
    newStudent.isActive = true;

    cout << "Enter Student Name (Max 49 chars): ";
    cin.ignore();
    string tempName;
    getline(cin, tempName);
    strncpy(newStudent.name, tempName.c_str(), 49);
    newStudent.name[49] = '\0'; 

    cout << "Enter Student Major (Max 49 chars): ";
    string tempMajor;
    getline(cin, tempMajor);
    strncpy(newStudent.major, tempMajor.c_str(), 49);
    newStudent.major[49] = '\0';
    
    ofstream outfile(FILENAME, ios::binary | ios::app);
    if (outfile.is_open()) {
        outfile.write((char*)&newStudent, RECORD_SIZE);
        outfile.close();
        cout << "\nStudent Record (ID: " << newStudent.id << ") added successfully.\n";
    } else {
        cout << "\nError: Unable to open file for writing.\n";
    }
}

// READ/SEARCH OPERATION (Direct Access)
void searchRecord() {
    int recordNum;
    cout << "Enter Record Number (ID) to search: ";
    cin >> recordNum;

    if (recordNum < 1) {
        cout << "Invalid record number.\n";
        return;
    }

    ifstream infile(FILENAME, ios::binary);
    if (!infile.is_open()) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    infile.seekg(getRecordOffset(recordNum));
    
    if (infile.fail() || infile.eof()) {
        cout << "Record not found (File boundary exceeded).\n";
        infile.close();
        return;
    }

    Student foundStudent;
    infile.read((char*)&foundStudent, RECORD_SIZE);
    infile.close();

    if (foundStudent.isActive) {
        cout << "\n--- Student Found ---\n";
        cout << "ID: " << foundStudent.id << "\n";
        cout << "Name: " << foundStudent.name << "\n";
        cout << "Major: " << foundStudent.major << "\n";
        cout << "---------------------\n";
    } else {
        cout << "Record " << recordNum << " found but is marked as deleted.\n";
    }
}

// UPDATE OPERATION (Direct Access)
void updateRecord() {
    int recordNum;
    cout << "Enter Record Number (ID) to update: ";
    cin >> recordNum;

    if (recordNum < 1) {
        cout << "Invalid record number.\n";
        return;
    }

    fstream file(FILENAME, ios::binary | ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Error: Unable to open file for update.\n";
        return;
    }

    file.seekg(getRecordOffset(recordNum));
    if (file.fail() || file.eof()) {
        cout << "Record " << recordNum << " not found (File boundary exceeded).\n";
        file.close();
        return;
    }

    Student currentStudent;
    file.read((char*)&currentStudent, RECORD_SIZE);
    
    if (!currentStudent.isActive) {
        cout << "Record " << recordNum << " is marked as deleted and cannot be updated.\n";
        file.close();
        return;
    }

    cout << "Current Name: " << currentStudent.name << "\n";
    cout << "Enter New Name (Max 49 chars, leave blank to keep current): ";
    cin.ignore();
    string newName;
    getline(cin, newName);

    if (!newName.empty()) {
        strncpy(currentStudent.name, newName.c_str(), 49);
        currentStudent.name[49] = '\0';
    }

    cout << "Current Major: " << currentStudent.major << "\n";
    cout << "Enter New Major (Max 49 chars, leave blank to keep current): ";
    string newMajor;
    getline(cin, newMajor);

    if (!newMajor.empty()) {
        strncpy(currentStudent.major, newMajor.c_str(), 49);
        currentStudent.major[49] = '\0';
    }

    file.seekp(getRecordOffset(recordNum));
    file.write((char*)&currentStudent, RECORD_SIZE);

    file.close();
    cout << "\nStudent Record " << recordNum << " updated successfully.\n";
}

// DELETE OPERATION (Soft Delete - Direct Access)
void deleteRecord() {
    int recordNum;
    cout << "Enter Record Number (ID) to delete: ";
    cin >> recordNum;

    if (recordNum < 1) {
        cout << "Invalid record number.\n";
        return;
    }

    fstream file(FILENAME, ios::binary | ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Error: Unable to open file for deletion.\n";
        return;
    }

    file.seekg(getRecordOffset(recordNum));
    if (file.fail() || file.eof()) {
        cout << "Record " << recordNum << " not found (File boundary exceeded).\n";
        file.close();
        return;
    }
    
    Student studentToDelete;
    file.read((char*)&studentToDelete, RECORD_SIZE);
    
    if (!studentToDelete.isActive) {
        cout << "Record " << recordNum << " is already deleted.\n";
        file.close();
        return;
    }
    
    studentToDelete.isActive = false;

    file.seekp(getRecordOffset(recordNum));
    file.write((char*)&studentToDelete, RECORD_SIZE);

    file.close();
    cout << "\nStudent Record " << recordNum << " deleted successfully.\n";
}

// READ ALL OPERATION
void displayAllRecords() {
    ifstream infile(FILENAME, ios::binary);
    if (!infile.is_open()) {
        cout << "Error: Unable to open file for reading.\n";
        return;
    }

    Student currentStudent;
    bool found = false;

    cout << "\n--- All Active Student Records ---\n";
    while (infile.read((char*)&currentStudent, RECORD_SIZE)) {
        if (currentStudent.isActive) {
            cout << "ID: " << currentStudent.id 
                 << ", Name: " << currentStudent.name 
                 << ", Major: " << currentStudent.major << "\n";
            found = true;
        }
    }
    
    infile.close();
    if (!found) {
        cout << "(No active records found.)\n";
    }
    cout << "----------------------------------\n";
}

// MAIN MENU
int main() {
    int choice;
    do {
        cout << "\n=== Student Information System (Direct Access) ===\n";
        cout << "1. Add New Student Record\n";
        cout << "2. Search Student Record (By ID)\n";
        cout << "3. Update Student Record\n";
        cout << "4. Delete Student Record\n";
        cout << "5. Display All Active Records\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0; 
        }

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                searchRecord();
                break;
            case 3:
                updateRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                displayAllRecords();
                break;
            case 6:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}