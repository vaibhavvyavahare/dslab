#include <iostream>
#include <string>
#include <limits> // Required for numeric_limits

using namespace std;

// Define the structure for a student record
struct Student {
    int rollNumber;
    string name;
    float marks;
};

const int MAX_RECORDS = 100;

// Function to safely get integer input
int getIntInput() {
    int input;
    while (!(cin >> input)) {
        cout << "Invalid input. Please enter an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

// Function to safely get float input
float getFloatInput() {
    float input;
    while (!(cin >> input)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

// 1. INPUT STUDENT RECORDS
int inputRecords(Student records[], int count) {
    char continueInput = 'y';
    while (count < MAX_RECORDS && (continueInput == 'y' || continueInput == 'Y')) {
        cout << "\n--- Input Record " << count + 1 << " ---\n";
        
        cout << "Enter Roll Number (Integer): ";
        records[count].rollNumber = getIntInput();
        
        cout << "Enter Name (String): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer before getline
        getline(cin, records[count].name);
        
        cout << "Enter Marks (Float): ";
        records[count].marks = getFloatInput();
        
        count++;

        if (count < MAX_RECORDS) {
            cout << "Do you want to enter another record? (y/n): ";
            cin >> continueInput;
        }
    }
    return count;
}

// 2. DISPLAY RECORDS
void displayRecords(const Student records[], int count) {
    if (count == 0) {
        cout << "\n(No records to display.)\n";
        return;
    }

    cout << "\n======================================================\n";
    cout << "Roll No. | Name                      | Marks\n";
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        // Basic formatting
        cout.width(8);
        cout << left << records[i].rollNumber << " | ";
        cout.width(25);
        cout << left << records[i].name << " | ";
        cout.precision(2);
        cout << fixed << records[i].marks << "\n";
    }
    cout << "======================================================\n";
}

// 3. SORTING IMPLEMENTATIONS (Using Selection Sort for simplicity)

// Utility function to swap two Student objects
void swapStudents(Student& a, Student& b) {
    Student temp = a;
    a = b;
    b = temp;
}

// SORT BY ROLL NUMBER (Ascending)
void sortByRollNumber(Student records[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < count; ++j) {
            if (records[j].rollNumber < records[min_idx].rollNumber) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swapStudents(records[i], records[min_idx]);
        }
    }
    cout << "\nRecords sorted by Roll Number (Ascending).\n";
}

// SORT BY NAME (Lexicographical/Alphabetical)
void sortByName(Student records[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < count; ++j) {
            // Lexicographical comparison
            if (records[j].name.compare(records[min_idx].name) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swapStudents(records[i], records[min_idx]);
        }
    }
    cout << "\nRecords sorted by Name (Lexicographical).\n";
}

// SORT BY MARKS (Descending)
void sortByMarks(Student records[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        int max_idx = i;
        for (int j = i + 1; j < count; ++j) {
            // Descending order, so we look for the maximum element
            if (records[j].marks > records[max_idx].marks) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swapStudents(records[i], records[max_idx]);
        }
    }
    cout << "\nRecords sorted by Marks (Descending).\n";
}

// MAIN FUNCTION AND MENU
int main() {
    Student studentRecords[MAX_RECORDS];
    int recordCount = 0;
    int choice;

    do {
        cout << "\n\n=== Student Record Management System ===\n";
        cout << "Current Records: " << recordCount << "/" << MAX_RECORDS << "\n";
        cout << "1. Input Student Records\n";
        cout << "2. Display Records (Current Order)\n";
        cout << "3. Sort by Roll Number (Ascending)\n";
        cout << "4. Sort by Name (Lexicographical)\n";
        cout << "5. Sort by Marks (Descending)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                recordCount = inputRecords(studentRecords, recordCount);
                break;
            case 2:
                displayRecords(studentRecords, recordCount);
                break;
            case 3:
                sortByRollNumber(studentRecords, recordCount);
                displayRecords(studentRecords, recordCount);
                break;
            case 4:
                sortByName(studentRecords, recordCount);
                displayRecords(studentRecords, recordCount);
                break;
            case 5:
                sortByMarks(studentRecords, recordCount);
                displayRecords(studentRecords, recordCount);
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select an option between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}