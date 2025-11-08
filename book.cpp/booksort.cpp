#include <iostream>
#include <string>

using namespace std;

struct Book {
    string title;
    string author;
    double price;
};

void displayBooks(const Book books[], int size) {
    cout << "--------------------------------------------------\n";
    cout << "Title (Alphabetical) | Author\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < size; ++i) {
        cout << books[i].title << " | " << books[i].author << "\n";
    }
    cout << "--------------------------------------------------\n";
}

void sortBooks(Book books[], int size) {
    int i, j;
    Book key; 

    for (i = 1; i < size; i++) {
        key = books[i];
        j = i - 1;

        while (j >= 0 && books[j].title.compare(key.title) > 0) {
            books[j + 1] = books[j];
            j = j - 1;
        }
        books[j + 1] = key;
    }
}

int main() {
    const int NUM_BOOKS = 5;
    Book inventory[NUM_BOOKS];

    inventory[0] = {"The Hitchhiker's Guide to the Galaxy", "Douglas Adams", 15.50};
    inventory[1] = {"A Tale of Two Cities", "Charles Dickens", 12.00};
    inventory[2] = {"The Secret History", "Donna Tartt", 20.99};
    inventory[3] = {"Dune", "Frank Herbert", 18.75};
    inventory[4] = {"Pride and Prejudice", "Jane Austen", 10.50};

    cout << "Online Bookstore Inventory Sorting Application\n";
    cout << "Initial list of books (unsorted):\n";
    displayBooks(inventory, NUM_BOOKS);

    sortBooks(inventory, NUM_BOOKS);

    cout << "\nBooks sorted alphabetically by title for seamless browsing:\n";
    displayBooks(inventory, NUM_BOOKS);

    return 0;
}