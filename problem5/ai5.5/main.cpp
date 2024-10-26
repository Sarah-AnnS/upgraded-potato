#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool is_checked_out;

    Book(int bookId, string bookTitle, string bookAuthor)
        : id(bookId), title(bookTitle), author(bookAuthor), is_checked_out(false) {}

    void displayInfo() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
             << ", Status: " << (is_checked_out ? "Checked Out" : "Available") << endl;
    }
};

class Library {
private:
    unordered_map<int, Book> books; // Book ID as key, Book object as value

public:
    void addBook(int id, const string &title, const string &author) {
        if (books.find(id) == books.end()) {
            books[id] = Book(id, title, author);
            cout << "Book added: " << title << endl;
        } else {
            cout << "Book with ID " << id << " already exists." << endl;
        }
    }

    void removeBook(int id) {
        if (books.erase(id)) {
            cout << "Book with ID " << id << " removed." << endl;
        } else {
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
    }

    void listAllBooks() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }
        for (const auto &pair : books) {
            pair.second.displayInfo();
        }
    }

    void checkoutBook(int id) {
        auto it = books.find(id);
        if (it != books.end()) {
            if (!it->second.is_checked_out) {
                it->second.is_checked_out = true;
                cout << "Book checked out: " << it->second.title << endl;
            } else {
                cout << "Book is already checked out." << endl;
            }
        } else {
            cout << "No book found with ID " << id << endl;
        }
    }

    void returnBook(int id) {
        auto it = books.find(id);
        if (it != books.end()) {
            if (it->second.is_checked_out) {
                it->second.is_checked_out = false;
                cout << "Book returned: " << it->second.title << endl;
            } else {
                cout << "Book was not checked out." << endl;
            }
        } else {
            cout << "No book found with ID " << id << endl;
        }
    }
};

int main() {
    Library library;
    int choice, id;
    string title, author;

    while (true) {
        cout << "\nLibrary Inventory System\n";
        cout << "1. Add Book\n2. Remove Book\n3. Search Book\n4. List All Books\n";
        cout << "5. Checkout Book\n6. Return Book\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter Book Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                library.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter Book ID to remove: ";
                cin >> id;
                library.removeBook(id);
                break;
            case 3:
                cout << "Enter Book ID to search: ";
                cin >> id;
                library.searchBook(id);
                break;
            case 4:
                library.listAllBooks();
                break;
            case 5:
                cout << "Enter Book ID to checkout: ";
                cin >> id;
                library.checkoutBook(id);
                break;
            case 6:
                cout << "Enter Book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            case 7:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
