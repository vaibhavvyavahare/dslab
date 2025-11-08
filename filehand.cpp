#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // Required for remove() and rename()

using namespace std;

const string FILENAME = "data.txt";
const string TEMP_FILENAME = "temp.txt";

// CREATE OPERATION
void createRecord(const string& content) {
    ofstream outfile(FILENAME, ios::app); 
    
    if (outfile.is_open()) {
        outfile << content << "\n";
        cout << "Record created/appended successfully.\n";
        outfile.close();
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

// READ OPERATION
void readAllRecords() {
    ifstream infile(FILENAME, ios::in); 
    string line;
    bool found = false;

    cout << "\n--- Current File Content ---\n";
    if (infile.is_open()) {
        while (getline(infile, line)) {
            cout << line << endl;
            found = true;
        }
        infile.close();
    } 
    
    if (!found) {
        cout << "(File is empty or could not be opened.)\n";
    }
    cout << "----------------------------\n";
}

// UPDATE OPERATION
void updateRecord(const string& oldText, const string& newText) {
    ifstream infile(FILENAME);
    ofstream outfile(TEMP_FILENAME);
    string line;
    bool updated = false;

    if (!infile.is_open() || !outfile.is_open()) {
        cout << "Unable to open files for update operation.\n";
        return;
    }

    while (getline(infile, line)) {
        size_t pos = line.find(oldText);
        if (pos != string::npos) {
            // Found the text, replace it and write the modified line
            line.replace(pos, oldText.length(), newText);
            updated = true;
        }
        // Write the (possibly modified) line to the temporary file
        outfile << line << "\n";
    }

    infile.close();
    outfile.close();

    // Delete original file and rename temporary file
    if (remove(FILENAME.c_str()) != 0) {
        cout << "Error deleting original file.\n";
        return;
    }
    if (rename(TEMP_FILENAME.c_str(), FILENAME.c_str()) != 0) {
        cout << "Error renaming temporary file.\n";
        return;
    }

    if (updated) {
        cout << "Record updated successfully.\n";
    } else {
        cout << "Old text not found for update.\n";
    }
}

// DELETE OPERATION
void deleteRecord(const string& lineToDelete) {
    ifstream infile(FILENAME);
    ofstream outfile(TEMP_FILENAME);
    string line;
    bool deleted = false;

    if (!infile.is_open() || !outfile.is_open()) {
        cout << "Unable to open files for delete operation.\n";
        return;
    }

    while (getline(infile, line)) {
        if (line != lineToDelete) {
            // If the line is NOT the one to delete, write it to the temporary file
            outfile << line << "\n";
        } else {
            // If the line IS the one to delete, skip writing it
            deleted = true;
        }
    }

    infile.close();
    outfile.close();

    // Delete original file and rename temporary file
    if (remove(FILENAME.c_str()) != 0) {
        cout << "Error deleting original file.\n";
        return;
    }
    if (rename(TEMP_FILENAME.c_str(), FILENAME.c_str()) != 0) {
        cout << "Error renaming temporary file.\n";
        return;
    }

    if (deleted) {
        cout << "Record deleted successfully.\n";
    } else {
        cout << "Line to delete not found.\n";
    }
}

// MAIN DEMONSTRATION
int main() {
    cout << "\n--- CREATE ---\n";
    createRecord("Item 1: Apple");
    createRecord("Item 2: Banana");
    createRecord("Item 3: Orange");
    
    cout << "\n--- READ ALL ---\n";
    readAllRecords();

    cout << "\n--- UPDATE ---\n";
    updateRecord("Banana", "Grapes"); 
    readAllRecords();

    cout << "\n--- DELETE ---\n";
    deleteRecord("Item 3: Orange"); 
    readAllRecords();

    return 0;
}
