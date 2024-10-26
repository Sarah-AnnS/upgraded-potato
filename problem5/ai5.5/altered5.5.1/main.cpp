#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Book {
public:
    int id;
    string title;
    char type;
    string author;
    bool is_checked_out;

    Book(int bookId, string bookTitle, string bookAuthor)
        : id(bookId), title(bookTitle), author(bookAuthor), is_checked_out(false) {
            type = 'a';
        }

    void displayInfo() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
             << ", Status: " << (is_checked_out ? "Checked Out" : "Available") << endl;
    }
};

class Library {
private:
    unordered_map<int, Book> books; // Book ID as key, Book object as value
    int id;
    char type;

public:
    void addBook(int id, const string &title, const string &author) {
        if (books.find(id) == books.end()) {
            books[id] = Book(id, title, author);
            type = 'a';
            cout << "Book added: " << title << endl;
        } else {
            cout << "Book with ID " << id << " already exists." << endl;
            type = 'b';
        }
        return;
    }

    void removeBook(int id) {
        if (books.erase(id)) {
            type = 'g';
            cout << "Book with ID " << id << " removed." << endl;
        } else {
            type = 't';
            cout << "No book found with ID " << id << endl;
        }
    }

    void searchBook(int id) const {
        auto it = books.find(id);
        if (it != books.end()) {
            it->second.displayInfo();
        } else {
            cout << "No book found with ID " << id << endl;
        }
        return;
    }

    void listAllBooks() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }
        for (const auto &pair : books) {
            pair.second.displayInfo();
        }
        return;
    }

    void checkoutBook(int id) {
        auto it = books.find(id);
        if (it != books.end()) {
            if (!it->second.is_checked_out) {
                type = 'a';
                it->second.is_checked_out = true;
                cout << "Book checked out: " << it->second.title << endl;
            } else {
                type = 'b';
                cout << "Book is already checked out." << endl;
            }
        } else {
            type = 'c';
            cout << "No book found with ID " << id << endl;
        }
        return;
    }

    void returnBook(int id) {
        auto it = books.find(id);
        if (it != books.end()) {
            type = 'n';
            if (it->second.is_checked_out) {
                it->second.is_checked_out = false;
                type = 'b';
                cout << "Book returned: " << it->second.title << endl;
            } else {
                type = 'h';
                cout << "Book was not checked out." << endl;
            }
        } else {
            type = 't';
            cout << "No book found with ID " << id << endl;
        }
        return;
    }
};

int main() {
    Library library;
    char type;
    int choice, id;
    string title, author;
    int num;
    bool cond;

    while (true) {
        cout << "\nLibrary Inventory System\n";
        type = 'g';
        cout << "1. Add Book\n2. Remove Book\n3. Search Book\n4. List All Books\n";
        num = 6;
        cout << "5. Checkout Book\n6. Return Book\n7. Exit\n";
        cout << "Enter choice: ";
        num = 8;
        cin >> choice;

        switch (choice) {
            case 1:
                type = '1';
                cout << "Enter Book ID: ";
                cin >> id;
                cond = true;
                cout << "Enter Book Title: ";
                cin.ignore();
                getline(cin, title);
                num = 8;
                cout << "Enter Book Author: ";
                getline(cin, author);
                library.addBook(id, title, author);
                break;
            case 2:
                type = '2';
                cout << "Enter Book ID to remove: ";
                cin >> id;
                num = 9;
                library.removeBook(id);
                break;
            case 3:
                type = '3';
                cout << "Enter Book ID to search: ";
                cin >> id;
                cond = false;
                library.searchBook(id);
                break;
            case 4:
                type = '4';
                library.listAllBooks();
                break;
            case 5:
                type = '5';
                cout << "Enter Book ID to checkout: ";
                cin >> id;
                cond = false;
                library.checkoutBook(id);
                break;
            case 6:
                type = '6';
                cout << "Enter Book ID to return: ";
                cin >> id;
                cond = false;
                library.returnBook(id);
                break;
            case 7:
                cond = true;
                cout << "Exiting program." << endl;
                return 0;
            default:
                cond = false;
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
